from bs4 import BeautifulSoup
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

with open("neon_intrinsics.csv", 'a') as file:
    file.write("ReturnType,Name,Arguments,Group\n")
    options = Options()
    options.add_argument('--headless')
    options.add_argument('--no-sandbox')
    options.add_argument('--disable-dev-shm-usage')
    driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)

    driver.get("https://developer.arm.com/architectures/instruction-sets/intrinsics/#f:@navigationhierarchiessimdisa=[Neon]")
    driver.maximize_window()
    driver.find_element(By.XPATH, "//button[text()='Accept and hide this message ']").click()
    wait = WebDriverWait(driver, 5)
    wait.until(EC.presence_of_element_located((By.CLASS_NAME, 'c-table')))

    sum = 0
    for i in range(0, 218):
        data = driver.page_source
        soup = BeautifulSoup(data, 'html.parser')
        table = soup.find_all(lambda tag: tag.name == "table" and tag.has_attr("class") and ("c-table" in tag.get("class")))[0]
        all_tr = table.find('tbody').find_all('tr')
        sum += len(all_tr)
        print(i, sum)
        for tr in all_tr:
            td = tr.find_all('td')
            file.write(f"{td[2].string},{td[3].string},\"{td[4].string}\",{td[5].string}\n")

        element = driver.find_element(By.TAG_NAME, "ads-pagination").shadow_root.find_element(By.CLASS_NAME, "c-pagination-action--next")
        # element.click()
        driver.execute_script("arguments[0].click();", element)
        wait = WebDriverWait(driver, 10)
        wait.until(EC.presence_of_element_located((By.CLASS_NAME, 'c-table')))
    driver.close()

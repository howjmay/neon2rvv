package main

import (
	"context"
	"fmt"
	"log"
	"time"

	"github.com/chromedp/chromedp"
)

type NeonInfo struct {
	ReturnType string
	Name       string
	Arguments  string
}

func main() {
	ctx, cancel := chromedp.NewContext(context.Background())
	defer cancel()

	ctx, cancel = context.WithTimeout(ctx, 30*time.Second)
	defer cancel()

	for i := 0; i < 2; i++ {
		pageString := ""
		if i != 0 {
			pageString = fmt.Sprintf("&first=%d", i*20)
		}
		url := "https://developer.arm.com/architectures/instruction-sets/intrinsics/#f:@navigationhierarchiessimdisa=[Neon]" + pageString
		xpaths := []string{}
		for j := 0; j < 20; j++ {
			// Define multiple XPaths
			childXpaths := []string{
				fmt.Sprintf(`//*[@id="app"]/div/div[2]/div[2]/main/div/div[2]/div[2]/div[3]/table/tbody/tr[%d]/td[3]/code`, j+1),
				fmt.Sprintf(`//*[@id="app"]/div/div[2]/div[2]/main/div/div[2]/div[2]/div[3]/table/tbody/tr[%d]/td[4]/code`, j+1),
				fmt.Sprintf(`//*[@id="app"]/div/div[2]/div[2]/main/div/div[2]/div[2]/div[3]/table/tbody/tr[%d]/td[5]/code`, j+1),
			}
			xpaths = append(xpaths, childXpaths...)
		}

		// JavaScript to query multiple XPaths and return their texts
		jsCode := "[]"
		for _, xpath := range xpaths {
			jsCode = fmt.Sprintf(`%s.concat(document.evaluate(%q, document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue ? document.evaluate(%q, document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue.textContent : "")`, jsCode, xpath, xpath)
		}

		var results []string
		err := chromedp.Run(ctx,
			chromedp.Navigate(url),
			chromedp.Sleep(5*time.Second), // Adjust based on actual page load times
			chromedp.Evaluate(jsCode, &results),
		)
		if err != nil {
			log.Fatalf("Failed to execute task: %v", err)
		}
		infos := []NeonInfo{}
		for j := 0; j < 20; j++ {
			infos = append(infos, NeonInfo{
				ReturnType: results[j*3],
				Name:       results[j*3+1],
				Arguments:  results[j*3+2],
			})

		}

		fmt.Println("results: ", infos)
	}

}

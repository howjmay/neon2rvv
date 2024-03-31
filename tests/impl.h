#ifndef NEON2RVV_TEST_H
#define NEON2RVV_TEST_H

#include "common.h"
#include "debug_tools.h"

#define INTRIN_LIST                                                              \
  /* vadd */                                                                     \
  _(vadd_s8)                                                                     \
  _(vadd_s16)                                                                    \
  _(vadd_s32)                                                                    \
  _(vadd_f32)                                                                    \
  _(vadd_u8)                                                                     \
  _(vadd_u16)                                                                    \
  _(vadd_u32)                                                                    \
  _(vadd_s64)                                                                    \
  _(vadd_u64)                                                                    \
  _(vaddq_s8)                                                                    \
  _(vaddq_s16)                                                                   \
  _(vaddq_s32)                                                                   \
  _(vaddq_s64)                                                                   \
  _(vaddq_f32)                                                                   \
  _(vadd_f64)                                                                    \
  _(vaddq_f64)                                                                   \
  _(vaddd_s64)                                                                   \
  _(vaddd_u64)                                                                   \
  _(vaddq_u8)                                                                    \
  _(vaddq_u16)                                                                   \
  _(vaddq_u32)                                                                   \
  _(vaddq_u64)                                                                   \
  _(vaddl_s8)                                                                    \
  _(vaddl_s16)                                                                   \
  _(vaddl_s32)                                                                   \
  _(vaddl_u8)                                                                    \
  _(vaddl_u16)                                                                   \
  _(vaddl_u32)                                                                   \
  _(vaddl_high_s8)                                                               \
  _(vaddl_high_s16)                                                              \
  _(vaddl_high_s32)                                                              \
  _(vaddl_high_u8)                                                               \
  _(vaddl_high_u16)                                                              \
  _(vaddl_high_u32)                                                              \
  _(vaddw_s8)                                                                    \
  _(vaddw_s16)                                                                   \
  _(vaddw_s32)                                                                   \
  _(vaddw_u8)                                                                    \
  _(vaddw_u16)                                                                   \
  _(vaddw_u32)                                                                   \
  _(vaddw_high_s8)                                                               \
  _(vaddw_high_s16)                                                              \
  _(vaddw_high_s32)                                                              \
  _(vaddw_high_u8)                                                               \
  _(vaddw_high_u16)                                                              \
  _(vaddw_high_u32)                                                              \
  _(vhadd_s8)                                                                    \
  _(vhadd_s16)                                                                   \
  _(vhadd_s32)                                                                   \
  _(vhadd_u8)                                                                    \
  _(vhadd_u16)                                                                   \
  _(vhadd_u32)                                                                   \
  _(vhaddq_s8)                                                                   \
  _(vhaddq_s16)                                                                  \
  _(vhaddq_s32)                                                                  \
  _(vhaddq_u8)                                                                   \
  _(vhaddq_u16)                                                                  \
  _(vhaddq_u32)                                                                  \
  _(vrhadd_s8)                                                                   \
  _(vrhadd_s16)                                                                  \
  _(vrhadd_s32)                                                                  \
  _(vrhadd_u8)                                                                   \
  _(vrhadd_u16)                                                                  \
  _(vrhadd_u32)                                                                  \
  _(vrhaddq_s8)                                                                  \
  _(vrhaddq_s16)                                                                 \
  _(vrhaddq_s32)                                                                 \
  _(vrhaddq_u8)                                                                  \
  _(vrhaddq_u16)                                                                 \
  _(vrhaddq_u32)                                                                 \
  _(vqadd_s8)                                                                    \
  _(vqadd_s16)                                                                   \
  _(vqadd_s32)                                                                   \
  _(vqadd_s64)                                                                   \
  _(vqadd_u8)                                                                    \
  _(vqadd_u16)                                                                   \
  _(vqadd_u32)                                                                   \
  _(vqadd_u64)                                                                   \
  _(vqaddq_s8)                                                                   \
  _(vqaddq_s16)                                                                  \
  _(vqaddq_s32)                                                                  \
  _(vqaddq_s64)                                                                  \
  _(vqaddq_u8)                                                                   \
  _(vqaddq_u16)                                                                  \
  _(vqaddq_u32)                                                                  \
  _(vqaddq_u64)                                                                  \
  /*_(vqaddb_s8)                                                              */ \
  /*_(vqaddh_s16)                                                             */ \
  /*_(vqadds_s32)                                                             */ \
  /*_(vqaddd_s64)                                                             */ \
  /*_(vqaddb_u8)                                                              */ \
  /*_(vqaddh_u16)                                                             */ \
  /*_(vqadds_u32)                                                             */ \
  /*_(vqaddd_u64)                                                             */ \
  /*_(vuqadd_s8)                                                              */ \
  /*_(vuqaddq_s8)                                                             */ \
  /*_(vuqadd_s16)                                                             */ \
  /*_(vuqaddq_s16)                                                            */ \
  /*_(vuqadd_s32)                                                             */ \
  /*_(vuqaddq_s32)                                                            */ \
  /*_(vuqadd_s64)                                                             */ \
  /*_(vuqaddq_s64)                                                            */ \
  /*_(vuqaddb_s8)                                                             */ \
  /*_(vuqaddh_s16)                                                            */ \
  /*_(vuqadds_s32)                                                            */ \
  /*_(vuqaddd_s64)                                                            */ \
  /*_(vsqadd_u8)                                                              */ \
  /*_(vsqaddq_u8)                                                             */ \
  /*_(vsqadd_u16)                                                             */ \
  /*_(vsqaddq_u16)                                                            */ \
  /*_(vsqadd_u32)                                                             */ \
  /*_(vsqaddq_u32)                                                            */ \
  /*_(vsqadd_u64)                                                             */ \
  /*_(vsqaddq_u64)                                                            */ \
  /*_(vsqaddb_u8)                                                             */ \
  /*_(vsqaddh_u16)                                                            */ \
  /*_(vsqadds_u32)                                                            */ \
  /*_(vsqaddd_u64)                                                            */ \
  _(vaddhn_s16)                                                                  \
  _(vaddhn_s32)                                                                  \
  _(vaddhn_s64)                                                                  \
  _(vaddhn_u16)                                                                  \
  _(vaddhn_u32)                                                                  \
  _(vaddhn_u64)                                                                  \
  /*_(vaddhn_high_s16)                                                        */ \
  /*_(vaddhn_high_s32)                                                        */ \
  /*_(vaddhn_high_s64)                                                        */ \
  /*_(vaddhn_high_u16)                                                        */ \
  /*_(vaddhn_high_u32)                                                        */ \
  /*_(vaddhn_high_u64)                                                        */ \
  _(vraddhn_s16)                                                                 \
  _(vraddhn_s32)                                                                 \
  _(vraddhn_s64)                                                                 \
  _(vraddhn_u16)                                                                 \
  _(vraddhn_u32)                                                                 \
  _(vraddhn_u64)                                                                 \
  /*_(vraddhn_high_s16)                                                       */ \
  /*_(vraddhn_high_s32)                                                       */ \
  /*_(vraddhn_high_s64)                                                       */ \
  /*_(vraddhn_high_u16)                                                       */ \
  /*_(vraddhn_high_u32)                                                       */ \
  /*_(vraddhn_high_u64)                                                       */ \
  _(vmul_s8)                                                                     \
  _(vmul_s16)                                                                    \
  _(vmul_s32)                                                                    \
  _(vmul_f32)                                                                    \
  _(vmul_u8)                                                                     \
  _(vmul_u16)                                                                    \
  _(vmul_u32)                                                                    \
  _(vmulq_s8)                                                                    \
  _(vmulq_s16)                                                                   \
  _(vmulq_s32)                                                                   \
  _(vmulq_f32)                                                                   \
  _(vmulq_u8)                                                                    \
  _(vmulq_u16)                                                                   \
  _(vmulq_u32)                                                                   \
  /*_(vmul_p8)                                                           */      \
  /*_(vmulq_p8)                                                          */      \
  /*_(vmul_f64)                                                               */ \
  /*_(vmulq_f64)                                                              */ \
  /*_(vmulx_f32)                                                              */ \
  /*_(vmulxq_f32)                                                             */ \
  /*_(vmulx_f64)                                                              */ \
  /*_(vmulxq_f64)                                                             */ \
  /*_(vmulxs_f32)                                                             */ \
  /*_(vmulxd_f64)                                                             */ \
  /*_(vmulx_lane_f32)                                                         */ \
  /*_(vmulxq_lane_f32)                                                        */ \
  /*_(vmulx_lane_f64)                                                         */ \
  /*_(vmulxq_lane_f64)                                                        */ \
  /*_(vmulxs_lane_f32)                                                        */ \
  /*_(vmulxd_lane_f64)                                                        */ \
  /*_(vmulx_laneq_f32)                                                        */ \
  /*_(vmulxq_laneq_f32)                                                       */ \
  /*_(vmulx_laneq_f64)                                                        */ \
  /*_(vmulxq_laneq_f64)                                                       */ \
  /*_(vmulxs_laneq_f32)                                                       */ \
  /*_(vmulxd_laneq_f64)                                                       */ \
  _(vdiv_f32)                                                                    \
  _(vdivq_f32)                                                                   \
  _(vdiv_f64)                                                                    \
  _(vdivq_f64)                                                                   \
  _(vqdmulh_s16)                                                                 \
  _(vqdmulh_s32)                                                                 \
  _(vqdmulhq_s16)                                                                \
  _(vqdmulhq_s32)                                                                \
  /*_(vqdmulhh_s16)                                                           */ \
  /*_(vqdmulhs_s32)                                                           */ \
  _(vqrdmulh_s16)                                                                \
  _(vqrdmulh_s32)                                                                \
  _(vqrdmulhq_s16)                                                               \
  _(vqrdmulhq_s32)                                                               \
  /*_(vqrdmulhh_s16)                                                          */ \
  /*_(vqrdmulhs_s32)                                                          */ \
  _(vqrdmlah_s16)                                                                \
  _(vqrdmlah_s32)                                                                \
  _(vqrdmlahq_s16)                                                               \
  _(vqrdmlahq_s32)                                                               \
  _(vqrdmlsh_s16)                                                                \
  _(vqrdmlsh_s32)                                                                \
  _(vqrdmlshq_s16)                                                               \
  _(vqrdmlshq_s32)                                                               \
  _(vmull_s8)                                                                    \
  _(vmull_s16)                                                                   \
  _(vmull_s32)                                                                   \
  _(vmull_u8)                                                                    \
  _(vmull_u16)                                                                   \
  _(vmull_u32)                                                                   \
  /*_(vmull_p8)                                                          */      \
  /*_(vmull_high_s8)                                                          */ \
  /*_(vmull_high_s16)                                                         */ \
  /*_(vmull_high_s32)                                                         */ \
  /*_(vmull_high_u8)                                                          */ \
  /*_(vmull_high_u16)                                                         */ \
  /*_(vmull_high_u32)                                                         */ \
  /*_(vmull_high_p8)                                                          */ \
  _(vqdmull_s16)                                                                 \
  _(vqdmull_s32)                                                                 \
  /*_(vqdmullh_s16)                                                           */ \
  /*_(vqdmulls_s32)                                                           */ \
  /*_(vqdmull_high_s16)                                                       */ \
  /*_(vqdmull_high_s32)                                                       */ \
  _(vmla_s8)                                                                     \
  _(vmla_s16)                                                                    \
  _(vmla_s32)                                                                    \
  _(vmla_f32)                                                                    \
  _(vmla_u8)                                                                     \
  _(vmla_u16)                                                                    \
  _(vmla_u32)                                                                    \
  _(vmlaq_s8)                                                                    \
  _(vmlaq_s16)                                                                   \
  _(vmlaq_s32)                                                                   \
  _(vmlaq_f32)                                                                   \
  /*_(vmla_f64)                                                               */ \
  /*_(vmlaq_f64)                                                              */ \
  _(vmlaq_u8)                                                                    \
  _(vmlaq_u16)                                                                   \
  _(vmlaq_u32)                                                                   \
  _(vmlal_s8)                                                                    \
  _(vmlal_s16)                                                                   \
  _(vmlal_s32)                                                                   \
  _(vmlal_u8)                                                                    \
  _(vmlal_u16)                                                                   \
  _(vmlal_u32)                                                                   \
  /*_(vmlal_high_s8)                                                          */ \
  /*_(vmlal_high_s16)                                                         */ \
  /*_(vmlal_high_s32)                                                         */ \
  /*_(vmlal_high_u8)                                                          */ \
  /*_(vmlal_high_u16)                                                         */ \
  /*_(vmlal_high_u32)                                                         */ \
  _(vqdmlal_s16)                                                                 \
  _(vqdmlal_s32)                                                                 \
  /*_(vqdmlalh_s16)                                                           */ \
  /*_(vqdmlals_s32)                                                           */ \
  /*_(vqdmlal_high_s16)                                                       */ \
  /*_(vqdmlal_high_s32)                                                       */ \
  _(vmls_s8)                                                                     \
  _(vmls_s16)                                                                    \
  _(vmls_s32)                                                                    \
  _(vmls_f32)                                                                    \
  _(vmls_u8)                                                                     \
  _(vmls_u16)                                                                    \
  _(vmls_u32)                                                                    \
  _(vmlsq_s8)                                                                    \
  _(vmlsq_s16)                                                                   \
  _(vmlsq_s32)                                                                   \
  _(vmlsq_f32)                                                                   \
  /*_(vmls_f64)                                                               */ \
  /*_(vmlsq_f64)                                                              */ \
  _(vmlsq_u8)                                                                    \
  _(vmlsq_u16)                                                                   \
  _(vmlsq_u32)                                                                   \
  _(vmlsl_s8)                                                                    \
  _(vmlsl_s16)                                                                   \
  _(vmlsl_s32)                                                                   \
  _(vmlsl_u8)                                                                    \
  _(vmlsl_u16)                                                                   \
  _(vmlsl_u32)                                                                   \
  /*_(vmlsl_high_s8)                                                          */ \
  /*_(vmlsl_high_s16)                                                         */ \
  /*_(vmlsl_high_s32)                                                         */ \
  /*_(vmlsl_high_u8)                                                          */ \
  /*_(vmlsl_high_u16)                                                         */ \
  /*_(vmlsl_high_u32)                                                         */ \
  _(vqdmlsl_s16)                                                                 \
  _(vqdmlsl_s32)                                                                 \
  /*_(vqdmlslh_s16)                                                           */ \
  /*_(vqdmlsls_s32)                                                           */ \
  /*_(vqdmlsl_high_s16)                                                       */ \
  /*_(vqdmlsl_high_s32)                                                       */ \
  _(vfma_f32)                                                                    \
  _(vfmaq_f32)                                                                   \
  /*_(vfma_f64)                                                               */ \
  /*_(vfmaq_f64)                                                              */ \
  /*_(vfma_lane_f32)                                                          */ \
  /*_(vfmaq_lane_f32)                                                         */ \
  /*_(vfma_lane_f64)                                                          */ \
  /*_(vfmaq_lane_f64)                                                         */ \
  /*_(vfmas_lane_f32)                                                         */ \
  /*_(vfmad_lane_f64)                                                         */ \
  /*_(vfma_laneq_f32)                                                         */ \
  /*_(vfmaq_laneq_f32)                                                        */ \
  /*_(vfma_laneq_f64)                                                         */ \
  /*_(vfmaq_laneq_f64)                                                        */ \
  /*_(vfmas_laneq_f32)                                                        */ \
  /*_(vfmad_laneq_f64)                                                        */ \
  _(vfms_f32)                                                                    \
  _(vfmsq_f32)                                                                   \
  /*_(vfms_f64)                                                               */ \
  /*_(vfmsq_f64)                                                              */ \
  /*_(vfms_lane_f32)                                                          */ \
  /*_(vfmsq_lane_f32)                                                         */ \
  /*_(vfms_lane_f64)                                                          */ \
  /*_(vfmsq_lane_f64)                                                         */ \
  /*_(vfmss_lane_f32)                                                         */ \
  /*_(vfmsd_lane_f64)                                                         */ \
  /*_(vfms_laneq_f32)                                                         */ \
  /*_(vfmsq_laneq_f32)                                                        */ \
  /*_(vfms_laneq_f64)                                                         */ \
  /*_(vfmsq_laneq_f64)                                                        */ \
  /*_(vfmss_laneq_f32)                                                        */ \
  /*_(vfmsd_laneq_f64)                                                        */ \
  _(vrndn_f32)                                                                   \
  _(vrndnq_f32)                                                                  \
  /*_(vrndn_f64)                                                              */ \
  /*_(vrndnq_f64)                                                             */ \
  /*_(vrndns_f32)                                                             */ \
  _(vrnda_f32)                                                                   \
  _(vrndaq_f32)                                                                  \
  /*_(vrnda_f64)                                                              */ \
  /*_(vrndaq_f64)                                                             */ \
  /*_(vrndi_f32)                                                              */ \
  /*_(vrndiq_f32)                                                             */ \
  /*_(vrndi_f64)                                                              */ \
  /*_(vrndiq_f64)                                                             */ \
  _(vrndp_f32)                                                                   \
  _(vrndpq_f32)                                                                  \
  /*_(vrndp_f64)                                                              */ \
  /*_(vrndpq_f64)                                                             */ \
  _(vrndm_f32)                                                                   \
  _(vrndmq_f32)                                                                  \
  /*_(vrndm_f64)                                                              */ \
  /*_(vrndmq_f64)                                                             */ \
  _(vrndx_f32)                                                                   \
  _(vrndxq_f32)                                                                  \
  /*_(vrndx_f64)                                                              */ \
  /*_(vrndxq_f64)                                                             */ \
  _(vrnd_f32)                                                                    \
  _(vrndq_f32)                                                                   \
  /*_(vrnd_f64)                                                               */ \
  /*_(vrndq_f64)                                                              */ \
  _(vsub_s8)                                                                     \
  _(vsub_s16)                                                                    \
  _(vsub_s32)                                                                    \
  _(vsub_f32)                                                                    \
  _(vsub_u8)                                                                     \
  _(vsub_u16)                                                                    \
  _(vsub_u32)                                                                    \
  _(vsub_s64)                                                                    \
  _(vsub_u64)                                                                    \
  _(vsubq_s8)                                                                    \
  _(vsubq_s16)                                                                   \
  _(vsubq_s32)                                                                   \
  _(vsubq_s64)                                                                   \
  _(vsubq_f32)                                                                   \
  /*_(vsub_f64)                                                               */ \
  /*_(vsubq_f64)                                                              */ \
  /*_(vsubd_s64)                                                              */ \
  /*_(vsubd_u64)                                                              */ \
  _(vsubq_u8)                                                                    \
  _(vsubq_u16)                                                                   \
  _(vsubq_u32)                                                                   \
  _(vsubq_u64)                                                                   \
  _(vsubl_s8)                                                                    \
  _(vsubl_s16)                                                                   \
  _(vsubl_s32)                                                                   \
  _(vsubl_u8)                                                                    \
  _(vsubl_u16)                                                                   \
  _(vsubl_u32)                                                                   \
  /*_(vsubl_high_s8)                                                          */ \
  /*_(vsubl_high_s16)                                                         */ \
  /*_(vsubl_high_s32)                                                         */ \
  /*_(vsubl_high_u8)                                                          */ \
  /*_(vsubl_high_u16)                                                         */ \
  /*_(vsubl_high_u32)                                                         */ \
  _(vsubw_s8)                                                                    \
  _(vsubw_s16)                                                                   \
  _(vsubw_s32)                                                                   \
  _(vsubw_u8)                                                                    \
  _(vsubw_u16)                                                                   \
  _(vsubw_u32)                                                                   \
  /*_(vsubw_high_s8)                                                          */ \
  /*_(vsubw_high_s16)                                                         */ \
  /*_(vsubw_high_s32)                                                         */ \
  /*_(vsubw_high_u8)                                                          */ \
  /*_(vsubw_high_u16)                                                         */ \
  /*_(vsubw_high_u32)                                                         */ \
  _(vhsub_s8)                                                                    \
  _(vhsub_s16)                                                                   \
  _(vhsub_s32)                                                                   \
  _(vhsub_u8)                                                                    \
  _(vhsub_u16)                                                                   \
  _(vhsub_u32)                                                                   \
  _(vhsubq_s8)                                                                   \
  _(vhsubq_s16)                                                                  \
  _(vhsubq_s32)                                                                  \
  _(vhsubq_u8)                                                                   \
  _(vhsubq_u16)                                                                  \
  _(vhsubq_u32)                                                                  \
  _(vqsub_s8)                                                                    \
  _(vqsub_s16)                                                                   \
  _(vqsub_s32)                                                                   \
  _(vqsub_s64)                                                                   \
  _(vqsub_u8)                                                                    \
  _(vqsub_u16)                                                                   \
  _(vqsub_u32)                                                                   \
  _(vqsub_u64)                                                                   \
  _(vqsubq_s8)                                                                   \
  _(vqsubq_s16)                                                                  \
  _(vqsubq_s32)                                                                  \
  _(vqsubq_s64)                                                                  \
  _(vqsubq_u8)                                                                   \
  _(vqsubq_u16)                                                                  \
  _(vqsubq_u32)                                                                  \
  _(vqsubq_u64)                                                                  \
  /*_(vqsubb_s8)                                                              */ \
  /*_(vqsubh_s16)                                                             */ \
  /*_(vqsubs_s32)                                                             */ \
  /*_(vqsubd_s64)                                                             */ \
  /*_(vqsubb_u8)                                                              */ \
  /*_(vqsubh_u16)                                                             */ \
  /*_(vqsubs_u32)                                                             */ \
  /*_(vqsubd_u64)                                                             */ \
  _(vsubhn_s16)                                                                  \
  _(vsubhn_s32)                                                                  \
  _(vsubhn_s64)                                                                  \
  _(vsubhn_u16)                                                                  \
  _(vsubhn_u32)                                                                  \
  _(vsubhn_u64)                                                                  \
  /*_(vsubhn_high_s16)                                                        */ \
  /*_(vsubhn_high_s32)                                                        */ \
  /*_(vsubhn_high_s64)                                                        */ \
  /*_(vsubhn_high_u16)                                                        */ \
  /*_(vsubhn_high_u32)                                                        */ \
  /*_(vsubhn_high_u64)                                                        */ \
  _(vrsubhn_s16)                                                                 \
  _(vrsubhn_s32)                                                                 \
  _(vrsubhn_s64)                                                                 \
  _(vrsubhn_u16)                                                                 \
  _(vrsubhn_u32)                                                                 \
  _(vrsubhn_u64)                                                                 \
  /*_(vrsubhn_high_s16)                                                       */ \
  /*_(vrsubhn_high_s32)                                                       */ \
  /*_(vrsubhn_high_s64)                                                       */ \
  /*_(vrsubhn_high_u16)                                                       */ \
  /*_(vrsubhn_high_u32)                                                       */ \
  /*_(vrsubhn_high_u64)                                                       */ \
  _(vceq_s8)                                                                     \
  _(vceq_s16)                                                                    \
  _(vceq_s32)                                                                    \
  _(vceq_f32)                                                                    \
  _(vceq_u8)                                                                     \
  _(vceq_u16)                                                                    \
  _(vceq_u32)                                                                    \
  /*_(vceq_p8)                                                           */      \
  _(vceqq_s8)                                                                    \
  _(vceqq_s16)                                                                   \
  _(vceqq_s32)                                                                   \
  _(vceqq_f32)                                                                   \
  _(vceqq_u8)                                                                    \
  _(vceqq_u16)                                                                   \
  _(vceqq_u32)                                                                   \
  /*_(vceqq_p8)                                                          */      \
  /*_(vceq_s64)                                                               */ \
  /*_(vceqq_s64)                                                              */ \
  /*_(vceq_u64)                                                               */ \
  /*_(vceqq_u64)                                                              */ \
  _(vcge_s8)                                                                     \
  _(vcge_s16)                                                                    \
  _(vcge_s32)                                                                    \
  _(vcge_f32)                                                                    \
  _(vcge_u8)                                                                     \
  _(vcge_u16)                                                                    \
  _(vcge_u32)                                                                    \
  _(vcgeq_s8)                                                                    \
  _(vcgeq_s16)                                                                   \
  _(vcgeq_s32)                                                                   \
  _(vcgeq_f32)                                                                   \
  /*_(vcge_s64)                                                               */ \
  /*_(vcgeq_s64)                                                              */ \
  /*_(vcge_u64)                                                               */ \
  /*_(vcgeq_u64)                                                              */ \
  /*_(vcge_f64)                                                               */ \
  /*_(vcgeq_f64)                                                              */ \
  /*_(vcged_s64)                                                              */ \
  /*_(vcged_u64)                                                              */ \
  /*_(vcges_f32)                                                              */ \
  /*_(vcged_f64)                                                              */ \
  /*_(vcgez_s8)                                                               */ \
  /*_(vcgezq_s8)                                                              */ \
  /*_(vcgez_s16)                                                              */ \
  /*_(vcgezq_s16)                                                             */ \
  /*_(vcgez_s32)                                                              */ \
  /*_(vcgezq_s32)                                                             */ \
  /*_(vcgez_s64)                                                              */ \
  /*_(vcgezq_s64)                                                             */ \
  /*_(vcgez_f32)                                                              */ \
  /*_(vcgezq_f32)                                                             */ \
  /*_(vcgez_f64)                                                              */ \
  /*_(vcgezq_f64)                                                             */ \
  /*_(vcgezd_s64)                                                             */ \
  /*_(vcgezs_f32)                                                             */ \
  /*_(vcgezd_f64)                                                             */ \
  _(vcgeq_u8)                                                                    \
  _(vcgeq_u16)                                                                   \
  _(vcgeq_u32)                                                                   \
  _(vcle_s8)                                                                     \
  _(vcle_s16)                                                                    \
  _(vcle_s32)                                                                    \
  _(vcle_f32)                                                                    \
  _(vcle_u8)                                                                     \
  _(vcle_u16)                                                                    \
  _(vcle_u32)                                                                    \
  _(vcleq_s8)                                                                    \
  _(vcleq_s16)                                                                   \
  _(vcleq_s32)                                                                   \
  _(vcleq_f32)                                                                   \
  /*_(vcle_s64)                                                               */ \
  /*_(vcleq_s64)                                                              */ \
  /*_(vcle_u64)                                                               */ \
  /*_(vcleq_u64)                                                              */ \
  /*_(vcle_f64)                                                               */ \
  /*_(vcleq_f64)                                                              */ \
  /*_(vcled_s64)                                                              */ \
  /*_(vcled_u64)                                                              */ \
  /*_(vcles_f32)                                                              */ \
  /*_(vcled_f64)                                                              */ \
  /*_(vclez_s8)                                                               */ \
  /*_(vclezq_s8)                                                              */ \
  /*_(vclez_s16)                                                              */ \
  /*_(vclezq_s16)                                                             */ \
  /*_(vclez_s32)                                                              */ \
  /*_(vclezq_s32)                                                             */ \
  /*_(vclez_s64)                                                              */ \
  /*_(vclezq_s64)                                                             */ \
  /*_(vclez_f32)                                                              */ \
  /*_(vclezq_f32)                                                             */ \
  /*_(vclez_f64)                                                              */ \
  /*_(vclezq_f64)                                                             */ \
  /*_(vclezd_s64)                                                             */ \
  /*_(vclezs_f32)                                                             */ \
  /*_(vclezd_f64)                                                             */ \
  _(vcleq_u8)                                                                    \
  _(vcleq_u16)                                                                   \
  _(vcleq_u32)                                                                   \
  _(vcgt_s8)                                                                     \
  _(vcgt_s16)                                                                    \
  _(vcgt_s32)                                                                    \
  _(vcgt_f32)                                                                    \
  _(vcgt_u8)                                                                     \
  _(vcgt_u16)                                                                    \
  _(vcgt_u32)                                                                    \
  _(vcgtq_s8)                                                                    \
  _(vcgtq_s16)                                                                   \
  _(vcgtq_s32)                                                                   \
  _(vcgtq_f32)                                                                   \
  /*_(vcgt_s64)                                                               */ \
  /*_(vcgtq_s64)                                                              */ \
  /*_(vcgt_u64)                                                               */ \
  /*_(vcgtq_u64)                                                              */ \
  /*_(vcgt_f64)                                                               */ \
  /*_(vcgtq_f64)                                                              */ \
  /*_(vcgtd_s64)                                                              */ \
  /*_(vcgtd_u64)                                                              */ \
  /*_(vcgts_f32)                                                              */ \
  /*_(vcgtd_f64)                                                              */ \
  /*_(vcgtz_s8)                                                               */ \
  /*_(vcgtzq_s8)                                                              */ \
  /*_(vcgtz_s16)                                                              */ \
  /*_(vcgtzq_s16)                                                             */ \
  /*_(vcgtz_s32)                                                              */ \
  /*_(vcgtzq_s32)                                                             */ \
  /*_(vcgtz_s64)                                                              */ \
  /*_(vcgtzq_s64)                                                             */ \
  /*_(vcgtz_f32)                                                              */ \
  /*_(vcgtzq_f32)                                                             */ \
  /*_(vcgtz_f64)                                                              */ \
  /*_(vcgtzq_f64)                                                             */ \
  /*_(vcgtzd_s64)                                                             */ \
  /*_(vcgtzs_f32)                                                             */ \
  /*_(vcgtzd_f64)                                                             */ \
  _(vcgtq_u8)                                                                    \
  _(vcgtq_u16)                                                                   \
  _(vcgtq_u32)                                                                   \
  _(vclt_s8)                                                                     \
  _(vclt_s16)                                                                    \
  _(vclt_s32)                                                                    \
  _(vclt_f32)                                                                    \
  _(vclt_u8)                                                                     \
  _(vclt_u16)                                                                    \
  _(vclt_u32)                                                                    \
  _(vcltq_s8)                                                                    \
  _(vcltq_s16)                                                                   \
  _(vcltq_s32)                                                                   \
  _(vcltq_f32)                                                                   \
  /*_(vclt_s64)                                                               */ \
  /*_(vcltq_s64)                                                              */ \
  /*_(vclt_u64)                                                               */ \
  /*_(vcltq_u64)                                                              */ \
  /*_(vclt_f64)                                                               */ \
  /*_(vcltq_f64)                                                              */ \
  /*_(vcltd_s64)                                                              */ \
  /*_(vcltd_u64)                                                              */ \
  /*_(vclts_f32)                                                              */ \
  /*_(vcltd_f64)                                                              */ \
  /*_(vcltz_s8)                                                               */ \
  /*_(vcltzq_s8)                                                              */ \
  /*_(vcltz_s16)                                                              */ \
  /*_(vcltzq_s16)                                                             */ \
  /*_(vcltz_s32)                                                              */ \
  /*_(vcltzq_s32)                                                             */ \
  /*_(vcltz_s64)                                                              */ \
  /*_(vcltzq_s64)                                                             */ \
  /*_(vcltz_f32)                                                              */ \
  /*_(vcltzq_f32)                                                             */ \
  /*_(vcltz_f64)                                                              */ \
  /*_(vcltzq_f64)                                                             */ \
  /*_(vcltzd_s64)                                                             */ \
  /*_(vcltzs_f32)                                                             */ \
  /*_(vcltzd_f64)                                                             */ \
  _(vcltq_u8)                                                                    \
  _(vcltq_u16)                                                                   \
  _(vcltq_u32)                                                                   \
  _(vabs_s8)                                                                     \
  _(vabs_s16)                                                                    \
  _(vabs_s32)                                                                    \
  _(vabs_f32)                                                                    \
  _(vabsq_s8)                                                                    \
  _(vabsq_s16)                                                                   \
  _(vabsq_s32)                                                                   \
  _(vabsq_f32)                                                                   \
  /*_(vabs_s64)                                                               */ \
  /*_(vabsd_s64)                                                              */ \
  /*_(vabsq_s64)                                                              */ \
  /*_(vabs_f64)                                                               */ \
  /*_(vabsq_f64)                                                              */ \
  _(vqabs_s8)                                                                    \
  _(vqabs_s16)                                                                   \
  _(vqabs_s32)                                                                   \
  _(vqabsq_s8)                                                                   \
  _(vqabsq_s16)                                                                  \
  _(vqabsq_s32)                                                                  \
  /*_(vqabs_s64)                                                              */ \
  /*_(vqabsq_s64)                                                             */ \
  /*_(vqabsb_s8)                                                              */ \
  /*_(vqabsh_s16)                                                             */ \
  /*_(vqabss_s32)                                                             */ \
  /*_(vqabsd_s64)                                                             */ \
  _(vcage_f32)                                                                   \
  _(vcageq_f32)                                                                  \
  /*_(vcage_f64)                                                              */ \
  /*_(vcageq_f64)                                                             */ \
  /*_(vcages_f32)                                                             */ \
  /*_(vcaged_f64)                                                             */ \
  _(vcale_f32)                                                                   \
  _(vcaleq_f32)                                                                  \
  /*_(vcale_f64)                                                              */ \
  /*_(vcaleq_f64)                                                             */ \
  /*_(vcales_f32)                                                             */ \
  /*_(vcaled_f64)                                                             */ \
  _(vcagt_f32)                                                                   \
  _(vcagtq_f32)                                                                  \
  /*_(vcagt_f64)                                                              */ \
  /*_(vcagtq_f64)                                                             */ \
  /*_(vcagts_f32)                                                             */ \
  /*_(vcagtd_f64)                                                             */ \
  _(vcalt_f32)                                                                   \
  _(vcaltq_f32)                                                                  \
  /*_(vcalt_f64)                                                              */ \
  /*_(vcaltq_f64)                                                             */ \
  /*_(vcalts_f32)                                                             */ \
  /*_(vcaltd_f64)                                                             */ \
  _(vtst_s8)                                                                     \
  _(vtst_s16)                                                                    \
  _(vtst_s32)                                                                    \
  _(vtst_u8)                                                                     \
  _(vtst_u16)                                                                    \
  _(vtst_u32)                                                                    \
  /*_(vtst_p8)                                                           */      \
  /*_(vtst_p16)                                                          */      \
  _(vtstq_s8)                                                                    \
  _(vtstq_s16)                                                                   \
  _(vtstq_s32)                                                                   \
  _(vtstq_u8)                                                                    \
  _(vtstq_u16)                                                                   \
  _(vtstq_u32)                                                                   \
  /*_(vtstq_p8)                                                          */      \
  /*_(vtst_s64)                                                               */ \
  /*_(vtstq_s64)                                                              */ \
  /*_(vtst_u64)                                                               */ \
  /*_(vtstq_u64)                                                              */ \
  /*_(vtstq_p16)                                                         */      \
  _(vabd_s8)                                                                     \
  _(vabd_s16)                                                                    \
  _(vabd_s32)                                                                    \
  _(vabd_f32)                                                                    \
  _(vabd_u8)                                                                     \
  _(vabd_u16)                                                                    \
  _(vabd_u32)                                                                    \
  _(vabdq_s8)                                                                    \
  _(vabdq_s16)                                                                   \
  _(vabdq_s32)                                                                   \
  _(vabdq_f32)                                                                   \
  /*_(vabd_f64)                                                               */ \
  /*_(vabdq_f64)                                                              */ \
  /*_(vabds_f32)                                                              */ \
  /*_(vabdd_f64)                                                              */ \
  _(vabdq_u8)                                                                    \
  _(vabdq_u16)                                                                   \
  _(vabdq_u32)                                                                   \
  _(vabdl_s8)                                                                    \
  _(vabdl_s16)                                                                   \
  _(vabdl_s32)                                                                   \
  _(vabdl_u8)                                                                    \
  _(vabdl_u16)                                                                   \
  _(vabdl_u32)                                                                   \
  /*_(vabdl_high_s8)                                                          */ \
  /*_(vabdl_high_s16)                                                         */ \
  /*_(vabdl_high_s32)                                                         */ \
  /*_(vabdl_high_u8)                                                          */ \
  /*_(vabdl_high_u16)                                                         */ \
  /*_(vabdl_high_u32)                                                         */ \
  _(vaba_s8)                                                                     \
  _(vaba_s16)                                                                    \
  _(vaba_s32)                                                                    \
  _(vaba_u8)                                                                     \
  _(vaba_u16)                                                                    \
  _(vaba_u32)                                                                    \
  _(vabaq_s8)                                                                    \
  _(vabaq_s16)                                                                   \
  _(vabaq_s32)                                                                   \
  _(vabaq_u8)                                                                    \
  _(vabaq_u16)                                                                   \
  _(vabaq_u32)                                                                   \
  _(vabal_s8)                                                                    \
  _(vabal_s16)                                                                   \
  _(vabal_s32)                                                                   \
  _(vabal_u8)                                                                    \
  _(vabal_u16)                                                                   \
  _(vabal_u32)                                                                   \
  /*_(vabal_high_s8)                                                          */ \
  /*_(vabal_high_s16)                                                         */ \
  /*_(vabal_high_s32)                                                         */ \
  /*_(vabal_high_u8)                                                          */ \
  /*_(vabal_high_u16)                                                         */ \
  /*_(vabal_high_u32)                                                         */ \
  _(vmax_s8)                                                                     \
  _(vmax_s16)                                                                    \
  _(vmax_s32)                                                                    \
  _(vmax_f32)                                                                    \
  _(vmax_u8)                                                                     \
  _(vmax_u16)                                                                    \
  _(vmax_u32)                                                                    \
  _(vmaxq_s8)                                                                    \
  _(vmaxq_s16)                                                                   \
  _(vmaxq_s32)                                                                   \
  _(vmaxq_f32)                                                                   \
  /*_(vmax_f64)                                                               */ \
  /*_(vmaxq_f64)                                                              */ \
  _(vmaxnm_f32)                                                                  \
  _(vmaxnmq_f32)                                                                 \
  /*_(vmaxnm_f64)                                                             */ \
  /*_(vmaxnmq_f64)                                                            */ \
  _(vminnm_f32)                                                                  \
  _(vminnmq_f32)                                                                 \
  /*_(vminnm_f64)                                                             */ \
  /*_(vminnmq_f64)                                                            */ \
  _(vmaxq_u8)                                                                    \
  _(vmaxq_u16)                                                                   \
  _(vmaxq_u32)                                                                   \
  _(vmin_s8)                                                                     \
  _(vmin_s16)                                                                    \
  _(vmin_s32)                                                                    \
  _(vmin_f32)                                                                    \
  _(vmin_u8)                                                                     \
  _(vmin_u16)                                                                    \
  _(vmin_u32)                                                                    \
  _(vminq_s8)                                                                    \
  _(vminq_s16)                                                                   \
  _(vminq_s32)                                                                   \
  _(vminq_f32)                                                                   \
  /*_(vmin_f64)                                                               */ \
  /*_(vminq_f64)                                                              */ \
  _(vminq_u8)                                                                    \
  _(vminq_u16)                                                                   \
  _(vminq_u32)                                                                   \
  _(vpadd_s8)                                                                    \
  _(vpadd_s16)                                                                   \
  _(vpadd_s32)                                                                   \
  _(vpadd_f32)                                                                   \
  /*_(vpaddq_s8)                                                              */ \
  /*_(vpaddq_s16)                                                             */ \
  /*_(vpaddq_s32)                                                             */ \
  /*_(vpaddq_s64)                                                             */ \
  /*_(vpaddq_u8)                                                              */ \
  /*_(vpaddq_u16)                                                             */ \
  /*_(vpaddq_u32)                                                             */ \
  /*_(vpaddq_u64)                                                             */ \
  /*_(vpaddq_f32)                                                             */ \
  /*_(vpaddq_f64)                                                             */ \
  _(vpadd_u8)                                                                    \
  _(vpadd_u16)                                                                   \
  _(vpadd_u32)                                                                   \
  _(vpaddl_s8)                                                                   \
  _(vpaddl_s16)                                                                  \
  _(vpaddl_s32)                                                                  \
  _(vpaddl_u8)                                                                   \
  _(vpaddl_u16)                                                                  \
  _(vpaddl_u32)                                                                  \
  _(vpaddlq_s8)                                                                  \
  _(vpaddlq_s16)                                                                 \
  _(vpaddlq_s32)                                                                 \
  _(vpaddlq_u8)                                                                  \
  _(vpaddlq_u16)                                                                 \
  _(vpaddlq_u32)                                                                 \
  _(vpadal_s8)                                                                   \
  _(vpadal_s16)                                                                  \
  _(vpadal_s32)                                                                  \
  _(vpadal_u8)                                                                   \
  _(vpadal_u16)                                                                  \
  _(vpadal_u32)                                                                  \
  _(vpadalq_s8)                                                                  \
  _(vpadalq_s16)                                                                 \
  _(vpadalq_s32)                                                                 \
  _(vpadalq_u8)                                                                  \
  _(vpadalq_u16)                                                                 \
  _(vpadalq_u32)                                                                 \
  _(vpmax_s8)                                                                    \
  _(vpmax_s16)                                                                   \
  _(vpmax_s32)                                                                   \
  _(vpmax_f32)                                                                   \
  /*_(vpmaxq_s8)                                                              */ \
  /*_(vpmaxq_s16)                                                             */ \
  /*_(vpmaxq_s32)                                                             */ \
  /*_(vpmaxq_u8)                                                              */ \
  /*_(vpmaxq_u16)                                                             */ \
  /*_(vpmaxq_u32)                                                             */ \
  /*_(vpmaxq_f32)                                                             */ \
  /*_(vpmaxq_f64)                                                             */ \
  _(vpmax_u8)                                                                    \
  _(vpmax_u16)                                                                   \
  _(vpmax_u32)                                                                   \
  _(vpmin_s8)                                                                    \
  _(vpmin_s16)                                                                   \
  _(vpmin_s32)                                                                   \
  _(vpmin_f32)                                                                   \
  /*_(vpminq_s8)                                                              */ \
  /*_(vpminq_s16)                                                             */ \
  /*_(vpminq_s32)                                                             */ \
  /*_(vpminq_u8)                                                              */ \
  /*_(vpminq_u16)                                                             */ \
  /*_(vpminq_u32)                                                             */ \
  /*_(vpminq_f32)                                                             */ \
  /*_(vpminq_f64)                                                             */ \
  /*_(vpmaxnm_f32)                                                            */ \
  /*_(vpmaxnmq_f32)                                                           */ \
  /*_(vpmaxnmq_f64)                                                           */ \
  /*_(vpminnm_f32)                                                            */ \
  /*_(vpminnmq_f32)                                                           */ \
  /*_(vpminnmq_f64)                                                           */ \
  /*_(vpaddd_s64)                                                             */ \
  /*_(vpaddd_u64)                                                             */ \
  /*_(vpadds_f32)                                                             */ \
  /*_(vpaddd_f64)                                                             */ \
  /*_(vpmaxs_f32)                                                             */ \
  /*_(vpmaxqd_f64)                                                            */ \
  /*_(vpmins_f32)                                                             */ \
  /*_(vpminqd_f64)                                                            */ \
  /*_(vpmaxnms_f32)                                                           */ \
  /*_(vpmaxnmqd_f64)                                                          */ \
  /*_(vpminnms_f32)                                                           */ \
  /*_(vpminnmqd_f64)                                                          */ \
  _(vaddv_s8)                                                                    \
  _(vaddvq_s8)                                                                   \
  _(vaddv_s16)                                                                   \
  _(vaddvq_s16)                                                                  \
  _(vaddv_s32)                                                                   \
  _(vaddvq_s32)                                                                  \
  _(vaddvq_s64)                                                                  \
  _(vaddv_u8)                                                                    \
  _(vaddvq_u8)                                                                   \
  _(vaddv_u16)                                                                   \
  _(vaddvq_u16)                                                                  \
  _(vaddv_u32)                                                                   \
  _(vaddvq_u32)                                                                  \
  _(vaddvq_u64)                                                                  \
  /*_(vaddv_f32)                                                              */ \
  /*_(vaddvq_f32)                                                             */ \
  /*_(vaddvq_f64)                                                             */ \
  /*_(vaddlv_s8)                                                              */ \
  /*_(vaddlvq_s8)                                                             */ \
  /*_(vaddlv_s16)                                                             */ \
  /*_(vaddlvq_s16)                                                            */ \
  /*_(vaddlv_s32)                                                             */ \
  /*_(vaddlvq_s32)                                                            */ \
  /*_(vaddlv_u8)                                                              */ \
  /*_(vaddlvq_u8)                                                             */ \
  /*_(vaddlv_u16)                                                             */ \
  /*_(vaddlvq_u16)                                                            */ \
  /*_(vaddlv_u32)                                                             */ \
  /*_(vaddlvq_u32)                                                            */ \
  /*_(vmaxv_s8)                                                               */ \
  /*_(vmaxvq_s8)                                                              */ \
  /*_(vmaxv_s16)                                                              */ \
  /*_(vmaxvq_s16)                                                             */ \
  /*_(vmaxv_s32)                                                              */ \
  /*_(vmaxvq_s32)                                                             */ \
  /*_(vmaxv_u8)                                                               */ \
  /*_(vmaxvq_u8)                                                              */ \
  /*_(vmaxv_u16)                                                              */ \
  /*_(vmaxvq_u16)                                                             */ \
  /*_(vmaxv_u32)                                                              */ \
  /*_(vmaxvq_u32)                                                             */ \
  /*_(vmaxv_f32)                                                              */ \
  /*_(vmaxvq_f32)                                                             */ \
  /*_(vmaxvq_f64)                                                             */ \
  /*_(vminv_s8)                                                               */ \
  /*_(vminvq_s8)                                                              */ \
  /*_(vminv_s16)                                                              */ \
  /*_(vminvq_s16)                                                             */ \
  /*_(vminv_s32)                                                              */ \
  /*_(vminvq_s32)                                                             */ \
  /*_(vminv_u8)                                                               */ \
  /*_(vminvq_u8)                                                              */ \
  /*_(vminv_u16)                                                              */ \
  /*_(vminvq_u16)                                                             */ \
  /*_(vminv_u32)                                                              */ \
  /*_(vminvq_u32)                                                             */ \
  /*_(vminv_f32)                                                              */ \
  /*_(vminvq_f32)                                                             */ \
  /*_(vminvq_f64)                                                             */ \
  /*_(vmaxnmv_f32)                                                            */ \
  /*_(vmaxnmvq_f32)                                                           */ \
  /*_(vmaxnmvq_f64)                                                           */ \
  /*_(vminnmv_f32)                                                            */ \
  /*_(vminnmvq_f32)                                                           */ \
  /*_(vminnmvq_f64)                                                           */ \
  _(vpmin_u8)                                                                    \
  _(vpmin_u16)                                                                   \
  _(vpmin_u32)                                                                   \
  _(vrecps_f32)                                                                  \
  _(vrecpsq_f32)                                                                 \
  /*_(vrecps_f64)                                                             */ \
  /*_(vrecpsq_f64)                                                            */ \
  /*_(vrecpss_f32)                                                            */ \
  /*_(vrecpsd_f64)                                                            */ \
  /*_(vsqrt_f32)                                                              */ \
  /*_(vsqrtq_f32)                                                             */ \
  /*_(vsqrt_f64)                                                              */ \
  /*_(vsqrtq_f64)                                                             */ \
  _(vrsqrts_f32)                                                                 \
  _(vrsqrtsq_f32)                                                                \
  /*_(vrsqrts_f64)                                                            */ \
  /*_(vrsqrtsq_f64)                                                           */ \
  /*_(vrsqrtss_f32)                                                           */ \
  /*_(vrsqrtsd_f64)                                                           */ \
  _(vshl_s8)                                                                     \
  _(vshl_s16)                                                                    \
  _(vshl_s32)                                                                    \
  _(vshl_s64)                                                                    \
  _(vshl_u8)                                                                     \
  _(vshl_u16)                                                                    \
  _(vshl_u32)                                                                    \
  _(vshl_u64)                                                                    \
  _(vshlq_s8)                                                                    \
  _(vshlq_s16)                                                                   \
  _(vshlq_s32)                                                                   \
  _(vshlq_s64)                                                                   \
  _(vshlq_u8)                                                                    \
  _(vshlq_u16)                                                                   \
  _(vshlq_u32)                                                                   \
  _(vshlq_u64)                                                                   \
  /*_(vshld_s64)                                                              */ \
  /*_(vshld_u64)                                                              */ \
  _(vrshl_s8)                                                                    \
  _(vrshl_s16)                                                                   \
  _(vrshl_s32)                                                                   \
  _(vrshl_s64)                                                                   \
  _(vrshl_u8)                                                                    \
  _(vrshl_u16)                                                                   \
  _(vrshl_u32)                                                                   \
  _(vrshl_u64)                                                                   \
  _(vrshlq_s8)                                                                   \
  _(vrshlq_s16)                                                                  \
  _(vrshlq_s32)                                                                  \
  _(vrshlq_s64)                                                                  \
  _(vrshlq_u8)                                                                   \
  _(vrshlq_u16)                                                                  \
  _(vrshlq_u32)                                                                  \
  _(vrshlq_u64)                                                                  \
  /*_(vrshld_s64)                                                             */ \
  /*_(vrshld_u64)                                                             */ \
  _(vqshl_s8)                                                                    \
  _(vqshl_s16)                                                                   \
  _(vqshl_s32)                                                                   \
  _(vqshl_s64)                                                                   \
  _(vqshl_u8)                                                                    \
  _(vqshl_u16)                                                                   \
  _(vqshl_u32)                                                                   \
  _(vqshl_u64)                                                                   \
  _(vqshlq_s8)                                                                   \
  _(vqshlq_s16)                                                                  \
  _(vqshlq_s32)                                                                  \
  _(vqshlq_s64)                                                                  \
  _(vqshlq_u8)                                                                   \
  _(vqshlq_u16)                                                                  \
  _(vqshlq_u32)                                                                  \
  _(vqshlq_u64)                                                                  \
  /*_(vqshlb_s8)                                                              */ \
  /*_(vqshlh_s16)                                                             */ \
  /*_(vqshls_s32)                                                             */ \
  /*_(vqshld_s64)                                                             */ \
  /*_(vqshlb_u8)                                                              */ \
  /*_(vqshlh_u16)                                                             */ \
  /*_(vqshls_u32)                                                             */ \
  /*_(vqshld_u64)                                                             */ \
  _(vqrshl_s8)                                                                   \
  _(vqrshl_s16)                                                                  \
  _(vqrshl_s32)                                                                  \
  _(vqrshl_s64)                                                                  \
  _(vqrshl_u8)                                                                   \
  _(vqrshl_u16)                                                                  \
  _(vqrshl_u32)                                                                  \
  _(vqrshl_u64)                                                                  \
  _(vqrshlq_s8)                                                                  \
  _(vqrshlq_s16)                                                                 \
  _(vqrshlq_s32)                                                                 \
  _(vqrshlq_s64)                                                                 \
  _(vqrshlq_u8)                                                                  \
  _(vqrshlq_u16)                                                                 \
  _(vqrshlq_u32)                                                                 \
  _(vqrshlq_u64)                                                                 \
  /*_(vqrshlb_s8)                                                             */ \
  /*_(vqrshlh_s16)                                                            */ \
  /*_(vqrshls_s32)                                                            */ \
  /*_(vqrshld_s64)                                                            */ \
  /*_(vqrshlb_u8)                                                             */ \
  /*_(vqrshlh_u16)                                                            */ \
  /*_(vqrshls_u32)                                                            */ \
  /*_(vqrshld_u64)                                                            */ \
  _(vshr_n_s8)                                                                   \
  _(vshr_n_s16)                                                                  \
  _(vshr_n_s32)                                                                  \
  _(vshr_n_s64)                                                                  \
  _(vshr_n_u8)                                                                   \
  _(vshr_n_u16)                                                                  \
  _(vshr_n_u32)                                                                  \
  _(vshr_n_u64)                                                                  \
  _(vshrq_n_s8)                                                                  \
  _(vshrq_n_s16)                                                                 \
  _(vshrq_n_s32)                                                                 \
  _(vshrq_n_s64)                                                                 \
  _(vshrq_n_u8)                                                                  \
  _(vshrq_n_u16)                                                                 \
  _(vshrq_n_u32)                                                                 \
  _(vshrq_n_u64)                                                                 \
  /*_(vshrd_n_s64)                                                            */ \
  /*_(vshrd_n_u64)                                                            */ \
  _(vrshr_n_s8)                                                                  \
  _(vrshr_n_s16)                                                                 \
  _(vrshr_n_s32)                                                                 \
  _(vrshr_n_s64)                                                                 \
  _(vrshr_n_u8)                                                                  \
  _(vrshr_n_u16)                                                                 \
  _(vrshr_n_u32)                                                                 \
  _(vrshr_n_u64)                                                                 \
  _(vrshrq_n_s8)                                                                 \
  _(vrshrq_n_s16)                                                                \
  _(vrshrq_n_s32)                                                                \
  _(vrshrq_n_s64)                                                                \
  _(vrshrq_n_u8)                                                                 \
  _(vrshrq_n_u16)                                                                \
  _(vrshrq_n_u32)                                                                \
  _(vrshrq_n_u64)                                                                \
  /*_(vrshrd_n_s64)                                                           */ \
  /*_(vrshrd_n_u64)                                                           */ \
  _(vshrn_n_s16)                                                                 \
  _(vshrn_n_s32)                                                                 \
  _(vshrn_n_s64)                                                                 \
  _(vshrn_n_u16)                                                                 \
  _(vshrn_n_u32)                                                                 \
  _(vshrn_n_u64)                                                                 \
  /*_(vshrn_high_n_s16)                                                       */ \
  /*_(vshrn_high_n_s32)                                                       */ \
  /*_(vshrn_high_n_s64)                                                       */ \
  /*_(vshrn_high_n_u16)                                                       */ \
  /*_(vshrn_high_n_u32)                                                       */ \
  /*_(vshrn_high_n_u64)                                                       */ \
  _(vrshrn_n_s16)                                                                \
  _(vrshrn_n_s32)                                                                \
  _(vrshrn_n_s64)                                                                \
  _(vrshrn_n_u16)                                                                \
  _(vrshrn_n_u32)                                                                \
  _(vrshrn_n_u64)                                                                \
  /*_(vrshrn_high_n_s16)                                                      */ \
  /*_(vrshrn_high_n_s32)                                                      */ \
  /*_(vrshrn_high_n_s64)                                                      */ \
  /*_(vrshrn_high_n_u16)                                                      */ \
  /*_(vrshrn_high_n_u32)                                                      */ \
  /*_(vrshrn_high_n_u64)                                                      */ \
  _(vqshrn_n_s16)                                                                \
  _(vqshrn_n_s32)                                                                \
  _(vqshrn_n_s64)                                                                \
  _(vqshrn_n_u16)                                                                \
  _(vqshrn_n_u32)                                                                \
  _(vqshrn_n_u64)                                                                \
  /*_(vqshrnh_n_s16)                                                          */ \
  /*_(vqshrns_n_s32)                                                          */ \
  /*_(vqshrnd_n_s64)                                                          */ \
  /*_(vqshrnh_n_u16)                                                          */ \
  /*_(vqshrns_n_u32)                                                          */ \
  /*_(vqshrnd_n_u64)                                                          */ \
  /*_(vqshrn_high_n_s16)                                                      */ \
  /*_(vqshrn_high_n_s32)                                                      */ \
  /*_(vqshrn_high_n_s64)                                                      */ \
  /*_(vqshrn_high_n_u16)                                                      */ \
  /*_(vqshrn_high_n_u32)                                                      */ \
  /*_(vqshrn_high_n_u64)                                                      */ \
  _(vqrshrn_n_s16)                                                               \
  _(vqrshrn_n_s32)                                                               \
  _(vqrshrn_n_s64)                                                               \
  _(vqrshrn_n_u16)                                                               \
  _(vqrshrn_n_u32)                                                               \
  _(vqrshrn_n_u64)                                                               \
  /*_(vqrshrnh_n_s16)                                                         */ \
  /*_(vqrshrns_n_s32)                                                         */ \
  /*_(vqrshrnd_n_s64)                                                         */ \
  /*_(vqrshrnh_n_u16)                                                         */ \
  /*_(vqrshrns_n_u32)                                                         */ \
  /*_(vqrshrnd_n_u64)                                                         */ \
  /*_(vqrshrn_high_n_s16)                                                     */ \
  /*_(vqrshrn_high_n_s32)                                                     */ \
  /*_(vqrshrn_high_n_s64)                                                     */ \
  /*_(vqrshrn_high_n_u16)                                                     */ \
  /*_(vqrshrn_high_n_u32)                                                     */ \
  /*_(vqrshrn_high_n_u64)                                                     */ \
  _(vqshrun_n_s16)                                                               \
  _(vqshrun_n_s32)                                                               \
  _(vqshrun_n_s64)                                                               \
  /*_(vqshrunh_n_s16)                                                         */ \
  /*_(vqshruns_n_s32)                                                         */ \
  /*_(vqshrund_n_s64)                                                         */ \
  /*_(vqshrun_high_n_s16)                                                     */ \
  /*_(vqshrun_high_n_s32)                                                     */ \
  /*_(vqshrun_high_n_s64)                                                     */ \
  _(vqrshrun_n_s16)                                                              \
  _(vqrshrun_n_s32)                                                              \
  _(vqrshrun_n_s64)                                                              \
  /*_(vqrshrunh_n_s16)                                                        */ \
  /*_(vqrshruns_n_s32)                                                        */ \
  /*_(vqrshrund_n_s64)                                                        */ \
  /*_(vqrshrun_high_n_s16)                                                    */ \
  /*_(vqrshrun_high_n_s32)                                                    */ \
  /*_(vqrshrun_high_n_s64)                                                    */ \
  _(vshl_n_s8)                                                                   \
  _(vshl_n_s16)                                                                  \
  _(vshl_n_s32)                                                                  \
  _(vshl_n_s64)                                                                  \
  _(vshl_n_u8)                                                                   \
  _(vshl_n_u16)                                                                  \
  _(vshl_n_u32)                                                                  \
  _(vshl_n_u64)                                                                  \
  _(vshlq_n_s8)                                                                  \
  _(vshlq_n_s16)                                                                 \
  _(vshlq_n_s32)                                                                 \
  _(vshlq_n_s64)                                                                 \
  _(vshlq_n_u8)                                                                  \
  _(vshlq_n_u16)                                                                 \
  _(vshlq_n_u32)                                                                 \
  _(vshlq_n_u64)                                                                 \
  /*_(vshld_n_s64)                                                            */ \
  /*_(vshld_n_u64)                                                            */ \
  _(vqshl_n_s8)                                                                  \
  _(vqshl_n_s16)                                                                 \
  _(vqshl_n_s32)                                                                 \
  _(vqshl_n_s64)                                                                 \
  _(vqshl_n_u8)                                                                  \
  _(vqshl_n_u16)                                                                 \
  _(vqshl_n_u32)                                                                 \
  _(vqshl_n_u64)                                                                 \
  _(vqshlq_n_s8)                                                                 \
  _(vqshlq_n_s16)                                                                \
  _(vqshlq_n_s32)                                                                \
  _(vqshlq_n_s64)                                                                \
  _(vqshlq_n_u8)                                                                 \
  _(vqshlq_n_u16)                                                                \
  _(vqshlq_n_u32)                                                                \
  _(vqshlq_n_u64)                                                                \
  /*_(vqshlb_n_s8)                                                            */ \
  /*_(vqshlh_n_s16)                                                           */ \
  /*_(vqshls_n_s32)                                                           */ \
  /*_(vqshld_n_s64)                                                           */ \
  /*_(vqshlb_n_u8)                                                            */ \
  /*_(vqshlh_n_u16)                                                           */ \
  /*_(vqshls_n_u32)                                                           */ \
  /*_(vqshld_n_u64)                                                           */ \
  _(vqshlu_n_s8)                                                                 \
  _(vqshlu_n_s16)                                                                \
  _(vqshlu_n_s32)                                                                \
  _(vqshlu_n_s64)                                                                \
  _(vqshluq_n_s8)                                                                \
  _(vqshluq_n_s16)                                                               \
  _(vqshluq_n_s32)                                                               \
  _(vqshluq_n_s64)                                                               \
  /*_(vqshlub_n_s8)                                                           */ \
  /*_(vqshluh_n_s16)                                                          */ \
  /*_(vqshlus_n_s32)                                                          */ \
  /*_(vqshlud_n_s64)                                                          */ \
  _(vshll_n_s8)                                                                  \
  _(vshll_n_s16)                                                                 \
  _(vshll_n_s32)                                                                 \
  _(vshll_n_u8)                                                                  \
  _(vshll_n_u16)                                                                 \
  _(vshll_n_u32)                                                                 \
  /*_(vshll_high_n_s8)                                                        */ \
  /*_(vshll_high_n_s16)                                                       */ \
  /*_(vshll_high_n_s32)                                                       */ \
  /*_(vshll_high_n_u8)                                                        */ \
  /*_(vshll_high_n_u16)                                                       */ \
  /*_(vshll_high_n_u32)                                                       */ \
  _(vsra_n_s8)                                                                   \
  _(vsra_n_s16)                                                                  \
  _(vsra_n_s32)                                                                  \
  _(vsra_n_s64)                                                                  \
  _(vsra_n_u8)                                                                   \
  _(vsra_n_u16)                                                                  \
  _(vsra_n_u32)                                                                  \
  _(vsra_n_u64)                                                                  \
  _(vsraq_n_s8)                                                                  \
  _(vsraq_n_s16)                                                                 \
  _(vsraq_n_s32)                                                                 \
  _(vsraq_n_s64)                                                                 \
  _(vsraq_n_u8)                                                                  \
  _(vsraq_n_u16)                                                                 \
  _(vsraq_n_u32)                                                                 \
  _(vsraq_n_u64)                                                                 \
  /*_(vsrad_n_s64)                                                            */ \
  /*_(vsrad_n_u64)                                                            */ \
  _(vrsra_n_s8)                                                                  \
  _(vrsra_n_s16)                                                                 \
  _(vrsra_n_s32)                                                                 \
  _(vrsra_n_s64)                                                                 \
  _(vrsra_n_u8)                                                                  \
  _(vrsra_n_u16)                                                                 \
  _(vrsra_n_u32)                                                                 \
  _(vrsra_n_u64)                                                                 \
  _(vrsraq_n_s8)                                                                 \
  _(vrsraq_n_s16)                                                                \
  _(vrsraq_n_s32)                                                                \
  _(vrsraq_n_s64)                                                                \
  _(vrsraq_n_u8)                                                                 \
  _(vrsraq_n_u16)                                                                \
  _(vrsraq_n_u32)                                                                \
  _(vrsraq_n_u64)                                                                \
  /*_(vrsrad_n_s64)                                                           */ \
  /*_(vrsrad_n_u64)                                                           */ \
  /*_(vsri_n_p64)                                                        */      \
  _(vsri_n_s8)                                                                   \
  _(vsri_n_s16)                                                                  \
  _(vsri_n_s32)                                                                  \
  _(vsri_n_s64)                                                                  \
  _(vsri_n_u8)                                                                   \
  _(vsri_n_u16)                                                                  \
  _(vsri_n_u32)                                                                  \
  _(vsri_n_u64)                                                                  \
  /*_(vsri_n_p8)                                                         */      \
  /*_(vsri_n_p16)                                                        */      \
  /*_(vsriq_n_p64)                                                       */      \
  _(vsriq_n_s8)                                                                  \
  _(vsriq_n_s16)                                                                 \
  _(vsriq_n_s32)                                                                 \
  _(vsriq_n_s64)                                                                 \
  _(vsriq_n_u8)                                                                  \
  _(vsriq_n_u16)                                                                 \
  _(vsriq_n_u32)                                                                 \
  _(vsriq_n_u64)                                                                 \
  /*_(vsriq_n_p8)                                                        */      \
  /*_(vsriq_n_p16)                                                       */      \
  /*_(vsrid_n_s64)                                                            */ \
  /*_(vsrid_n_u64)                                                            */ \
  /*_(vsli_n_p64)                                                        */      \
  _(vsli_n_s8)                                                                   \
  _(vsli_n_s16)                                                                  \
  _(vsli_n_s32)                                                                  \
  _(vsli_n_s64)                                                                  \
  _(vsli_n_u8)                                                                   \
  _(vsli_n_u16)                                                                  \
  _(vsli_n_u32)                                                                  \
  _(vsli_n_u64)                                                                  \
  /*_(vsli_n_p8)                                                         */      \
  /*_(vsli_n_p16)                                                        */      \
  /*_(vsliq_n_p64)                                                       */      \
  _(vsliq_n_s8)                                                                  \
  _(vsliq_n_s16)                                                                 \
  _(vsliq_n_s32)                                                                 \
  _(vsliq_n_s64)                                                                 \
  _(vsliq_n_u8)                                                                  \
  _(vsliq_n_u16)                                                                 \
  _(vsliq_n_u32)                                                                 \
  _(vsliq_n_u64)                                                                 \
  /*_(vsliq_n_p8)                                                        */      \
  /*_(vsliq_n_p16)                                                       */      \
  /*_(vslid_n_s64)                                                            */ \
  /*_(vslid_n_u64)                                                            */ \
  _(vneg_s8)                                                                     \
  _(vneg_s16)                                                                    \
  _(vneg_s32)                                                                    \
  _(vneg_f32)                                                                    \
  _(vnegq_s8)                                                                    \
  _(vnegq_s16)                                                                   \
  _(vnegq_s32)                                                                   \
  _(vnegq_f32)                                                                   \
  /*_(vneg_s64)                                                               */ \
  /*_(vnegd_s64)                                                              */ \
  /*_(vnegq_s64)                                                              */ \
  /*_(vneg_f64)                                                               */ \
  /*_(vnegq_f64)                                                              */ \
  _(vqneg_s8)                                                                    \
  _(vqneg_s16)                                                                   \
  _(vqneg_s32)                                                                   \
  _(vqnegq_s8)                                                                   \
  _(vqnegq_s16)                                                                  \
  _(vqnegq_s32)                                                                  \
  /*_(vqneg_s64)                                                              */ \
  /*_(vqnegq_s64)                                                             */ \
  /*_(vqnegb_s8)                                                              */ \
  /*_(vqnegh_s16)                                                             */ \
  /*_(vqnegs_s32)                                                             */ \
  /*_(vqnegd_s64)                                                             */ \
  _(vmvn_s8)                                                                     \
  _(vmvn_s16)                                                                    \
  _(vmvn_s32)                                                                    \
  _(vmvn_u8)                                                                     \
  _(vmvn_u16)                                                                    \
  _(vmvn_u32)                                                                    \
  /*_(vmvn_p8)                                                           */      \
  _(vmvnq_s8)                                                                    \
  _(vmvnq_s16)                                                                   \
  _(vmvnq_s32)                                                                   \
  _(vmvnq_u8)                                                                    \
  _(vmvnq_u16)                                                                   \
  _(vmvnq_u32)                                                                   \
  /*_(vmvnq_p8)                                                          */      \
  _(vcls_s8)                                                                     \
  _(vcls_s16)                                                                    \
  _(vcls_s32)                                                                    \
  _(vclsq_s8)                                                                    \
  _(vclsq_s16)                                                                   \
  _(vclsq_s32)                                                                   \
  /*_(vcls_u8)                                                                */ \
  /*_(vclsq_u8)                                                               */ \
  /*_(vcls_u16)                                                               */ \
  /*_(vclsq_u16)                                                              */ \
  /*_(vcls_u32)                                                               */ \
  /*_(vclsq_u32)                                                              */ \
  _(vclz_s8)                                                                     \
  _(vclz_s16)                                                                    \
  _(vclz_s32)                                                                    \
  _(vclz_u8)                                                                     \
  _(vclz_u16)                                                                    \
  _(vclz_u32)                                                                    \
  _(vclzq_s8)                                                                    \
  _(vclzq_s16)                                                                   \
  _(vclzq_s32)                                                                   \
  _(vclzq_u8)                                                                    \
  _(vclzq_u16)                                                                   \
  _(vclzq_u32)                                                                   \
  _(vcnt_s8)                                                                     \
  _(vcnt_u8)                                                                     \
  /*_(vcnt_p8)                                                           */      \
  _(vcntq_s8)                                                                    \
  _(vcntq_u8)                                                                    \
  /*_(vcntq_p8)                                                          */      \
  _(vrecpe_f32)                                                                  \
  _(vrecpe_u32)                                                                  \
  _(vrecpeq_f32)                                                                 \
  /*_(vrecpe_f64)                                                             */ \
  /*_(vrecpeq_f64)                                                            */ \
  /*_(vrecpes_f32)                                                            */ \
  /*_(vrecped_f64)                                                            */ \
  _(vrecpeq_u32)                                                                 \
  _(vrsqrte_f32)                                                                 \
  _(vrsqrte_u32)                                                                 \
  _(vrsqrteq_f32)                                                                \
  /*_(vrsqrte_f64)                                                            */ \
  /*_(vrsqrteq_f64)                                                           */ \
  /*_(vrsqrtes_f32)                                                           */ \
  /*_(vrsqrted_f64)                                                           */ \
  _(vrsqrteq_u32)                                                                \
  _(vget_lane_s8)                                                                \
  _(vget_lane_s16)                                                               \
  _(vget_lane_s32)                                                               \
  _(vget_lane_f32)                                                               \
  /*_(vget_lane_f64)                                                          */ \
  _(vget_lane_u8)                                                                \
  _(vget_lane_u16)                                                               \
  _(vget_lane_u32)                                                               \
  /*_(vget_lane_p8)                                                      */      \
  /*_(vget_lane_p16)                                                     */      \
  _(vget_lane_s64)                                                               \
  /*_(vget_lane_p64)                                                     */      \
  _(vget_lane_u64)                                                               \
  _(vgetq_lane_s8)                                                               \
  _(vgetq_lane_s16)                                                              \
  _(vgetq_lane_s32)                                                              \
  _(vgetq_lane_f32)                                                              \
  /*_(vgetq_lane_f64)                                                         */ \
  _(vgetq_lane_u8)                                                               \
  _(vgetq_lane_u16)                                                              \
  _(vgetq_lane_u32)                                                              \
  /*_(vgetq_lane_p8)                                                     */      \
  /*_(vgetq_lane_p16)                                                    */      \
  /*_(vget_lane_f16)                                                          */ \
  /*_(vgetq_lane_f16)                                                         */ \
  _(vgetq_lane_s64)                                                              \
  /*_(vgetq_lane_p64)                                                    */      \
  _(vgetq_lane_u64)                                                              \
  _(vset_lane_s8)                                                                \
  _(vset_lane_s16)                                                               \
  _(vset_lane_s32)                                                               \
  _(vset_lane_f32)                                                               \
  /*_(vset_lane_f64)                                                          */ \
  _(vset_lane_u8)                                                                \
  _(vset_lane_u16)                                                               \
  _(vset_lane_u32)                                                               \
  /*_(vset_lane_p8)                                                      */      \
  /*_(vset_lane_p16)                                                     */      \
  /*_(vset_lane_f16)                                                          */ \
  /*_(vsetq_lane_f16)                                                         */ \
  _(vset_lane_s64)                                                               \
  _(vset_lane_u64)                                                               \
  /*_(vset_lane_p64)                                                     */      \
  _(vsetq_lane_s8)                                                               \
  _(vsetq_lane_s16)                                                              \
  _(vsetq_lane_s32)                                                              \
  _(vsetq_lane_f32)                                                              \
  /*_(vsetq_lane_f64)                                                         */ \
  /*_(vrecpxs_f32)                                                            */ \
  /*_(vrecpxd_f64)                                                            */ \
  /*_(vfma_n_f32)                                                             */ \
  /*_(vfmaq_n_f32)                                                            */ \
  /*_(vfms_n_f32)                                                             */ \
  /*_(vfmsq_n_f32)                                                            */ \
  /*_(vfma_n_f64)                                                             */ \
  /*_(vfmaq_n_f64)                                                            */ \
  /*_(vfms_n_f64)                                                             */ \
  /*_(vfmsq_n_f64)                                                            */ \
  _(vsetq_lane_u8)                                                               \
  _(vsetq_lane_u16)                                                              \
  _(vsetq_lane_u32)                                                              \
  /*_(vsetq_lane_p8)                                                     */      \
  /*_(vsetq_lane_p16)                                                    */      \
  _(vsetq_lane_s64)                                                              \
  _(vsetq_lane_u64)                                                              \
  /*_(vsetq_lane_p64)                                                    */      \
  /*_(vcreate_p64)                                                       */      \
  _(vcreate_s8)                                                                  \
  _(vcreate_s16)                                                                 \
  _(vcreate_s32)                                                                 \
  _(vcreate_s64)                                                                 \
  /*_(vcreate_f16)                                                       */      \
  _(vcreate_f32)                                                                 \
  _(vcreate_u8)                                                                  \
  _(vcreate_u16)                                                                 \
  _(vcreate_u32)                                                                 \
  _(vcreate_u64)                                                                 \
  /*_(vcreate_p8)                                                        */      \
  /*_(vcreate_p16)                                                       */      \
  /*_(vcreate_f64)                                                            */ \
  _(vdup_n_s8)                                                                   \
  _(vdup_n_s16)                                                                  \
  _(vdup_n_s32)                                                                  \
  _(vdup_n_f32)                                                                  \
  _(vdup_n_u8)                                                                   \
  _(vdup_n_u16)                                                                  \
  _(vdup_n_u32)                                                                  \
  /*_(vdup_n_p8)                                                         */      \
  /*_(vdup_n_p16)                                                        */      \
  /*_(vdup_n_p64)                                                        */      \
  _(vdup_n_s64)                                                                  \
  _(vdup_n_u64)                                                                  \
  /*_(vdupq_n_p64)                                                       */      \
  _(vdupq_n_s8)                                                                  \
  _(vdupq_n_s16)                                                                 \
  _(vdupq_n_s32)                                                                 \
  _(vdupq_n_f32)                                                                 \
  _(vdupq_n_u8)                                                                  \
  _(vdupq_n_u16)                                                                 \
  _(vdupq_n_u32)                                                                 \
  /*_(vdupq_n_p8)                                                        */      \
  /*_(vdupq_n_p16)                                                       */      \
  /*_(vdup_n_f64)                                                             */ \
  /*_(vdupq_n_f64)                                                            */ \
  _(vdupq_n_s64)                                                                 \
  _(vdupq_n_u64)                                                                 \
  _(vmov_n_s8)                                                                   \
  _(vmov_n_s16)                                                                  \
  _(vmov_n_s32)                                                                  \
  _(vmov_n_f32)                                                                  \
  _(vmov_n_u8)                                                                   \
  _(vmov_n_u16)                                                                  \
  _(vmov_n_u32)                                                                  \
  /*_(vmov_n_p8)                                                         */      \
  /*_(vmov_n_p16)                                                        */      \
  _(vmov_n_s64)                                                                  \
  _(vmov_n_u64)                                                                  \
  _(vmovq_n_s8)                                                                  \
  _(vmovq_n_s16)                                                                 \
  _(vmovq_n_s32)                                                                 \
  _(vmovq_n_f32)                                                                 \
  _(vmovq_n_u8)                                                                  \
  _(vmovq_n_u16)                                                                 \
  _(vmovq_n_u32)                                                                 \
  /*_(vmovq_n_p8)                                                        */      \
  /*_(vmovq_n_p16)                                                       */      \
  /*_(vmov_n_f64)                                                             */ \
  /*_(vmovq_n_f64)                                                            */ \
  _(vmovq_n_s64)                                                                 \
  _(vmovq_n_u64)                                                                 \
  _(vdup_lane_s8)                                                                \
  _(vdup_lane_s16)                                                               \
  _(vdup_lane_s32)                                                               \
  _(vdup_lane_f32)                                                               \
  _(vdup_lane_u8)                                                                \
  _(vdup_lane_u16)                                                               \
  _(vdup_lane_u32)                                                               \
  /*_(vdup_lane_p8)                                                      */      \
  /*_(vdup_lane_p16)                                                     */      \
  /*_(vdup_lane_p64)                                                     */      \
  _(vdup_lane_s64)                                                               \
  _(vdup_lane_u64)                                                               \
  _(vdupq_lane_s8)                                                               \
  _(vdupq_lane_s16)                                                              \
  _(vdupq_lane_s32)                                                              \
  _(vdupq_lane_f32)                                                              \
  _(vdupq_lane_u8)                                                               \
  _(vdupq_lane_u16)                                                              \
  _(vdupq_lane_u32)                                                              \
  /*_(vdupq_lane_p8)                                                     */      \
  /*_(vdupq_lane_p16)                                                    */      \
  /*_(vdup_lane_f64)                                                          */ \
  /*_(vdupq_lane_f64)                                                         */ \
  /*_(vdup_laneq_s8)                                                          */ \
  /*_(vdupq_laneq_s8)                                                         */ \
  /*_(vdup_laneq_s16)                                                         */ \
  /*_(vdupq_laneq_s16)                                                        */ \
  /*_(vdup_laneq_s32)                                                         */ \
  /*_(vdupq_laneq_s32)                                                        */ \
  /*_(vdup_laneq_s64)                                                         */ \
  /*_(vdupq_laneq_s64)                                                        */ \
  /*_(vdup_laneq_u8)                                                          */ \
  /*_(vdupq_laneq_u8)                                                         */ \
  /*_(vdup_laneq_u16)                                                         */ \
  /*_(vdupq_laneq_u16)                                                        */ \
  /*_(vdup_laneq_u32)                                                         */ \
  /*_(vdupq_laneq_u32)                                                        */ \
  /*_(vdup_laneq_u64)                                                         */ \
  /*_(vdupq_laneq_u64)                                                        */ \
  /*_(vdup_laneq_p64)                                                         */ \
  /*_(vdupq_laneq_p64)                                                        */ \
  /*_(vdup_laneq_f32)                                                         */ \
  /*_(vdupq_laneq_f32)                                                        */ \
  /*_(vdup_laneq_p8)                                                          */ \
  /*_(vdupq_laneq_p8)                                                         */ \
  /*_(vdup_laneq_p16)                                                         */ \
  /*_(vdupq_laneq_p16)                                                        */ \
  /*_(vdup_laneq_f64)                                                         */ \
  /*_(vdupq_laneq_f64)                                                        */ \
  /*_(vdupq_lane_p64)                                                    */      \
  _(vdupq_lane_s64)                                                              \
  _(vdupq_lane_u64)                                                              \
  /*_(vcombine_p64)                                                      */      \
  _(vcombine_s8)                                                                 \
  _(vcombine_s16)                                                                \
  _(vcombine_s32)                                                                \
  _(vcombine_s64)                                                                \
  /*_(vcombine_f16)                                                      */      \
  _(vcombine_f32)                                                                \
  _(vcombine_u8)                                                                 \
  _(vcombine_u16)                                                                \
  _(vcombine_u32)                                                                \
  _(vcombine_u64)                                                                \
  /*_(vcombine_p8)                                                       */      \
  /*_(vcombine_p16)                                                      */      \
  /*_(vcombine_f64)                                                           */ \
  /*_(vget_high_p64)                                                     */      \
  _(vget_high_s8)                                                                \
  _(vget_high_s16)                                                               \
  _(vget_high_s32)                                                               \
  _(vget_high_s64)                                                               \
  /*_(vget_high_f16)                                                     */      \
  _(vget_high_f32)                                                               \
  _(vget_high_u8)                                                                \
  _(vget_high_u16)                                                               \
  _(vget_high_u32)                                                               \
  _(vget_high_u64)                                                               \
  /*_(vget_high_p8)                                                      */      \
  /*_(vget_high_p16)                                                     */      \
  /*_(vget_high_f64)                                                          */ \
  _(vget_low_s8)                                                                 \
  _(vget_low_s16)                                                                \
  _(vget_low_s32)                                                                \
  /*_(vget_low_f16)                                                      */      \
  _(vget_low_f32)                                                                \
  _(vget_low_u8)                                                                 \
  _(vget_low_u16)                                                                \
  _(vget_low_u32)                                                                \
  /*_(vget_low_p8)                                                       */      \
  /*_(vget_low_p16)                                                      */      \
  /*_(vget_low_f64)                                                           */ \
  /*_(vdupb_lane_s8)                                                          */ \
  /*_(vduph_lane_s16)                                                         */ \
  /*_(vdups_lane_s32)                                                         */ \
  /*_(vdupd_lane_s64)                                                         */ \
  /*_(vdupb_lane_u8)                                                          */ \
  /*_(vduph_lane_u16)                                                         */ \
  /*_(vdups_lane_u32)                                                         */ \
  /*_(vdupd_lane_u64)                                                         */ \
  /*_(vdups_lane_f32)                                                         */ \
  /*_(vdupd_lane_f64)                                                         */ \
  /*_(vdupb_lane_p8)                                                          */ \
  /*_(vduph_lane_p16)                                                         */ \
  /*_(vdupb_laneq_s8)                                                         */ \
  /*_(vduph_laneq_s16)                                                        */ \
  /*_(vdups_laneq_s32)                                                        */ \
  /*_(vdupd_laneq_s64)                                                        */ \
  /*_(vdupb_laneq_u8)                                                         */ \
  /*_(vduph_laneq_u16)                                                        */ \
  /*_(vdups_laneq_u32)                                                        */ \
  /*_(vdupd_laneq_u64)                                                        */ \
  /*_(vdups_laneq_f32)                                                        */ \
  /*_(vdupd_laneq_f64)                                                        */ \
  /*_(vdupb_laneq_p8)                                                         */ \
  /*_(vduph_laneq_p16)                                                        */ \
  /*_(vget_low_p64)                                                      */      \
  _(vget_low_s64)                                                                \
  _(vget_low_u64)                                                                \
  _(vcvt_s32_f32)                                                                \
  _(vcvt_f32_s32)                                                                \
  _(vcvt_f32_u32)                                                                \
  _(vcvt_u32_f32)                                                                \
  _(vcvtq_s32_f32)                                                               \
  _(vcvtq_f32_s32)                                                               \
  _(vcvtq_f32_u32)                                                               \
  /*_(vcvts_f32_s32)                                                          */ \
  /*_(vcvts_f32_u32)                                                          */ \
  /*_(vcvt_f64_s64)                                                           */ \
  /*_(vcvtq_f64_s64)                                                          */ \
  /*_(vcvt_f64_u64)                                                           */ \
  /*_(vcvtq_f64_u64)                                                          */ \
  /*_(vcvtd_f64_s64)                                                          */ \
  /*_(vcvtd_f64_u64)                                                          */ \
  _(vcvtq_u32_f32)                                                               \
  /*_(vcvtn_s32_f32)                                                          */ \
  /*_(vcvtnq_s32_f32)                                                         */ \
  /*_(vcvtn_u32_f32)                                                          */ \
  /*_(vcvtnq_u32_f32)                                                         */ \
  /*_(vcvtm_s32_f32)                                                          */ \
  /*_(vcvtmq_s32_f32)                                                         */ \
  /*_(vcvtm_u32_f32)                                                          */ \
  /*_(vcvtmq_u32_f32)                                                         */ \
  /*_(vcvtp_s32_f32)                                                          */ \
  /*_(vcvtpq_s32_f32)                                                         */ \
  /*_(vcvtp_u32_f32)                                                          */ \
  /*_(vcvtpq_u32_f32)                                                         */ \
  /*_(vcvta_s32_f32)                                                          */ \
  /*_(vcvtaq_s32_f32)                                                         */ \
  /*_(vcvta_u32_f32)                                                          */ \
  /*_(vcvtaq_u32_f32)                                                         */ \
  /*_(vcvts_s32_f32)                                                          */ \
  /*_(vcvts_u32_f32)                                                          */ \
  /*_(vcvtns_s32_f32)                                                         */ \
  /*_(vcvtns_u32_f32)                                                         */ \
  /*_(vcvtms_s32_f32)                                                         */ \
  /*_(vcvtms_u32_f32)                                                         */ \
  /*_(vcvtps_s32_f32)                                                         */ \
  /*_(vcvtps_u32_f32)                                                         */ \
  /*_(vcvtas_s32_f32)                                                         */ \
  /*_(vcvtas_u32_f32)                                                         */ \
  /*_(vcvt_s64_f64)                                                           */ \
  /*_(vcvtq_s64_f64)                                                          */ \
  /*_(vcvt_u64_f64)                                                           */ \
  /*_(vcvtq_u64_f64)                                                          */ \
  /*_(vcvtn_s64_f64)                                                          */ \
  /*_(vcvtnq_s64_f64)                                                         */ \
  /*_(vcvtn_u64_f64)                                                          */ \
  /*_(vcvtnq_u64_f64)                                                         */ \
  /*_(vcvtm_s64_f64)                                                          */ \
  /*_(vcvtmq_s64_f64)                                                         */ \
  /*_(vcvtm_u64_f64)                                                          */ \
  /*_(vcvtmq_u64_f64)                                                         */ \
  /*_(vcvtp_s64_f64)                                                          */ \
  /*_(vcvtpq_s64_f64)                                                         */ \
  /*_(vcvtp_u64_f64)                                                          */ \
  /*_(vcvtpq_u64_f64)                                                         */ \
  /*_(vcvta_s64_f64)                                                          */ \
  /*_(vcvtaq_s64_f64)                                                         */ \
  /*_(vcvta_u64_f64)                                                          */ \
  /*_(vcvtaq_u64_f64)                                                         */ \
  /*_(vcvtd_s64_f64)                                                          */ \
  /*_(vcvtd_u64_f64)                                                          */ \
  /*_(vcvtnd_s64_f64)                                                         */ \
  /*_(vcvtnd_u64_f64)                                                         */ \
  /*_(vcvtmd_s64_f64)                                                         */ \
  /*_(vcvtmd_u64_f64)                                                         */ \
  /*_(vcvtpd_s64_f64)                                                         */ \
  /*_(vcvtpd_u64_f64)                                                         */ \
  /*_(vcvtad_s64_f64)                                                         */ \
  /*_(vcvtad_u64_f64)                                                         */ \
  /*_(vcvt_f16_f32)                                                      */      \
  /*_(vcvt_high_f16_f32)                                                      */ \
  /*_(vcvt_f32_f64)                                                           */ \
  /*_(vcvt_high_f32_f64)                                                      */ \
  /*_(vcvt_f32_f16)                                                      */      \
  /*_(vcvt_high_f32_f16)                                                      */ \
  /*_(vcvt_f64_f32)                                                           */ \
  /*_(vcvt_high_f64_f32)                                                      */ \
  /*_(vcvtx_f32_f64)                                                          */ \
  /*_(vcvtxd_f32_f64)                                                         */ \
  /*_(vcvtx_high_f32_f64)                                                     */ \
  _(vcvt_n_s32_f32)                                                              \
  _(vcvt_n_f32_s32)                                                              \
  _(vcvt_n_f32_u32)                                                              \
  _(vcvt_n_u32_f32)                                                              \
  _(vcvtq_n_s32_f32)                                                             \
  _(vcvtq_n_f32_s32)                                                             \
  _(vcvtq_n_f32_u32)                                                             \
  /*_(vcvts_n_f32_s32)                                                        */ \
  /*_(vcvts_n_f32_u32)                                                        */ \
  /*_(vcvt_n_f64_s64)                                                         */ \
  /*_(vcvtq_n_f64_s64)                                                        */ \
  /*_(vcvt_n_f64_u64)                                                         */ \
  /*_(vcvtq_n_f64_u64)                                                        */ \
  /*_(vcvtd_n_f64_s64)                                                        */ \
  /*_(vcvtd_n_f64_u64)                                                        */ \
  _(vcvtq_n_u32_f32)                                                             \
  /*_(vcvts_n_s32_f32)                                                        */ \
  /*_(vcvts_n_u32_f32)                                                        */ \
  /*_(vcvt_n_s64_f64)                                                         */ \
  /*_(vcvtq_n_s64_f64)                                                        */ \
  /*_(vcvt_n_u64_f64)                                                         */ \
  /*_(vcvtq_n_u64_f64)                                                        */ \
  /*_(vcvtd_n_s64_f64)                                                        */ \
  /*_(vcvtd_n_u64_f64)                                                        */ \
  _(vmovn_s16)                                                                   \
  _(vmovn_s32)                                                                   \
  _(vmovn_s64)                                                                   \
  _(vmovn_u16)                                                                   \
  _(vmovn_u32)                                                                   \
  _(vmovn_u64)                                                                   \
  /*_(vmovn_high_s16)                                                         */ \
  /*_(vmovn_high_s32)                                                         */ \
  /*_(vmovn_high_s64)                                                         */ \
  /*_(vmovn_high_u16)                                                         */ \
  /*_(vmovn_high_u32)                                                         */ \
  /*_(vmovn_high_u64)                                                         */ \
  _(vqmovn_s16)                                                                  \
  _(vqmovn_s32)                                                                  \
  _(vqmovn_s64)                                                                  \
  _(vqmovn_u16)                                                                  \
  _(vqmovn_u32)                                                                  \
  _(vqmovn_u64)                                                                  \
  /*_(vqmovnh_s16)                                                            */ \
  /*_(vqmovns_s32)                                                            */ \
  /*_(vqmovnd_s64)                                                            */ \
  /*_(vqmovnh_u16)                                                            */ \
  /*_(vqmovns_u32)                                                            */ \
  /*_(vqmovnd_u64)                                                            */ \
  /*_(vqmovn_high_s16)                                                        */ \
  /*_(vqmovn_high_s32)                                                        */ \
  /*_(vqmovn_high_s64)                                                        */ \
  /*_(vqmovn_high_u16)                                                        */ \
  /*_(vqmovn_high_u32)                                                        */ \
  /*_(vqmovn_high_u64)                                                        */ \
  _(vqmovun_s16)                                                                 \
  _(vqmovun_s32)                                                                 \
  _(vqmovun_s64)                                                                 \
  /*_(vqmovunh_s16)                                                           */ \
  /*_(vqmovuns_s32)                                                           */ \
  /*_(vqmovund_s64)                                                           */ \
  /*_(vqmovun_high_s16)                                                       */ \
  /*_(vqmovun_high_s32)                                                       */ \
  /*_(vqmovun_high_s64)                                                       */ \
  _(vmovl_s8)                                                                    \
  _(vmovl_s16)                                                                   \
  _(vmovl_s32)                                                                   \
  _(vmovl_u8)                                                                    \
  _(vmovl_u16)                                                                   \
  _(vmovl_u32)                                                                   \
  /*_(vmovl_high_s8)                                                          */ \
  /*_(vmovl_high_s16)                                                         */ \
  /*_(vmovl_high_s32)                                                         */ \
  /*_(vmovl_high_u8)                                                          */ \
  /*_(vmovl_high_u16)                                                         */ \
  /*_(vmovl_high_u32)                                                         */ \
  _(vtbl1_s8)                                                                    \
  _(vtbl1_u8)                                                                    \
  /*_(vtbl1_p8)                                                          */      \
  _(vtbl2_s8)                                                                    \
  _(vtbl2_u8)                                                                    \
  /*_(vtbl2_p8)                                                          */      \
  _(vtbl3_s8)                                                                    \
  _(vtbl3_u8)                                                                    \
  /*_(vtbl3_p8)                                                          */      \
  _(vtbl4_s8)                                                                    \
  _(vtbl4_u8)                                                                    \
  /*_(vtbl4_p8)                                                          */      \
  _(vtbx1_s8)                                                                    \
  _(vtbx1_u8)                                                                    \
  /*_(vtbx1_p8)                                                          */      \
  _(vtbx2_s8)                                                                    \
  _(vtbx2_u8)                                                                    \
  /*_(vtbx2_p8)                                                          */      \
  _(vtbx3_s8)                                                                    \
  _(vtbx3_u8)                                                                    \
  /*_(vtbx3_p8)                                                          */      \
  _(vtbx4_s8)                                                                    \
  _(vtbx4_u8)                                                                    \
  /*_(vtbx4_p8)                                                          */      \
  /*_(vqtbl1_s8)                                                              */ \
  /*_(vqtbl1q_s8)                                                             */ \
  /*_(vqtbl1_u8)                                                              */ \
  /*_(vqtbl1q_u8)                                                             */ \
  /*_(vqtbl1_p8)                                                              */ \
  /*_(vqtbl1q_p8)                                                             */ \
  /*_(vqtbx1_s8)                                                              */ \
  /*_(vqtbx1q_s8)                                                             */ \
  /*_(vqtbx1_u8)                                                              */ \
  /*_(vqtbx1q_u8)                                                             */ \
  /*_(vqtbx1_p8)                                                              */ \
  /*_(vqtbx1q_p8)                                                             */ \
  /*_(vqtbl2_s8)                                                              */ \
  /*_(vqtbl2q_s8)                                                             */ \
  /*_(vqtbl2_u8)                                                              */ \
  /*_(vqtbl2q_u8)                                                             */ \
  /*_(vqtbl2_p8)                                                              */ \
  /*_(vqtbl2q_p8)                                                             */ \
  /*_(vqtbl3_s8)                                                              */ \
  /*_(vqtbl3q_s8)                                                             */ \
  /*_(vqtbl3_u8)                                                              */ \
  /*_(vqtbl3q_u8)                                                             */ \
  /*_(vqtbl3_p8)                                                              */ \
  /*_(vqtbl3q_p8)                                                             */ \
  /*_(vqtbl4_s8)                                                              */ \
  /*_(vqtbl4q_s8)                                                             */ \
  /*_(vqtbl4_u8)                                                              */ \
  /*_(vqtbl4q_u8)                                                             */ \
  /*_(vqtbl4_p8)                                                              */ \
  /*_(vqtbl4q_p8)                                                             */ \
  /*_(vqtbx2_s8)                                                              */ \
  /*_(vqtbx2q_s8)                                                             */ \
  /*_(vqtbx2_u8)                                                              */ \
  /*_(vqtbx2q_u8)                                                             */ \
  /*_(vqtbx2_p8)                                                              */ \
  /*_(vqtbx2q_p8)                                                             */ \
  /*_(vqtbx3_s8)                                                              */ \
  /*_(vqtbx3q_s8)                                                             */ \
  /*_(vqtbx3_u8)                                                              */ \
  /*_(vqtbx3q_u8)                                                             */ \
  /*_(vqtbx3_p8)                                                              */ \
  /*_(vqtbx3q_p8)                                                             */ \
  /*_(vqtbx4_s8)                                                              */ \
  /*_(vqtbx4q_s8)                                                             */ \
  /*_(vqtbx4_u8)                                                              */ \
  /*_(vqtbx4q_u8)                                                             */ \
  /*_(vqtbx4_p8)                                                              */ \
  /*_(vqtbx4q_p8)                                                             */ \
  _(vmul_lane_s16)                                                               \
  _(vmul_lane_s32)                                                               \
  _(vmul_lane_f32)                                                               \
  _(vmul_lane_u16)                                                               \
  _(vmul_lane_u32)                                                               \
  _(vmulq_lane_s16)                                                              \
  _(vmulq_lane_s32)                                                              \
  _(vmulq_lane_f32)                                                              \
  /*_(vmul_lane_f64)                                                          */ \
  /*_(vmulq_lane_f64)                                                         */ \
  /*_(vmuls_lane_f32)                                                         */ \
  /*_(vmuld_lane_f64)                                                         */ \
  /*_(vmul_laneq_s16)                                                         */ \
  /*_(vmulq_laneq_s16)                                                        */ \
  /*_(vmul_laneq_s32)                                                         */ \
  /*_(vmulq_laneq_s32)                                                        */ \
  /*_(vmul_laneq_u16)                                                         */ \
  /*_(vmulq_laneq_u16)                                                        */ \
  /*_(vmul_laneq_u32)                                                         */ \
  /*_(vmulq_laneq_u32)                                                        */ \
  /*_(vmul_laneq_f32)                                                         */ \
  /*_(vmulq_laneq_f32)                                                        */ \
  /*_(vmul_laneq_f64)                                                         */ \
  /*_(vmulq_laneq_f64)                                                        */ \
  /*_(vmuls_laneq_f32)                                                        */ \
  /*_(vmuld_laneq_f64)                                                        */ \
  _(vmulq_lane_u16)                                                              \
  _(vmulq_lane_u32)                                                              \
  _(vmla_lane_s16)                                                               \
  _(vmla_lane_s32)                                                               \
  _(vmla_lane_f32)                                                               \
  _(vmla_lane_u16)                                                               \
  _(vmla_lane_u32)                                                               \
  _(vmlaq_lane_s16)                                                              \
  _(vmlaq_lane_s32)                                                              \
  _(vmlaq_lane_f32)                                                              \
  /*_(vmla_laneq_s16)                                                         */ \
  /*_(vmlaq_laneq_s16)                                                        */ \
  /*_(vmla_laneq_s32)                                                         */ \
  /*_(vmlaq_laneq_s32)                                                        */ \
  /*_(vmla_laneq_u16)                                                         */ \
  /*_(vmlaq_laneq_u16)                                                        */ \
  /*_(vmla_laneq_u32)                                                         */ \
  /*_(vmlaq_laneq_u32)                                                        */ \
  /*_(vmla_laneq_f32)                                                         */ \
  /*_(vmlaq_laneq_f32)                                                        */ \
  _(vmlaq_lane_u16)                                                              \
  _(vmlaq_lane_u32)                                                              \
  _(vmlal_lane_s16)                                                              \
  _(vmlal_lane_s32)                                                              \
  _(vmlal_lane_u16)                                                              \
  _(vmlal_lane_u32)                                                              \
  /*_(vmlal_high_lane_s16)                                                    */ \
  /*_(vmlal_high_lane_s32)                                                    */ \
  /*_(vmlal_high_lane_u16)                                                    */ \
  /*_(vmlal_high_lane_u32)                                                    */ \
  /*_(vmlal_laneq_s16)                                                        */ \
  /*_(vmlal_laneq_s32)                                                        */ \
  /*_(vmlal_laneq_u16)                                                        */ \
  /*_(vmlal_laneq_u32)                                                        */ \
  /*_(vmlal_high_laneq_s16)                                                   */ \
  /*_(vmlal_high_laneq_s32)                                                   */ \
  /*_(vmlal_high_laneq_u16)                                                   */ \
  /*_(vmlal_high_laneq_u32)                                                   */ \
  _(vqdmlal_lane_s16)                                                            \
  _(vqdmlal_lane_s32)                                                            \
  /*_(vqdmlalh_lane_s16)                                                      */ \
  /*_(vqdmlals_lane_s32)                                                      */ \
  /*_(vqdmlal_high_lane_s16)                                                  */ \
  /*_(vqdmlal_high_lane_s32)                                                  */ \
  /*_(vqdmlal_laneq_s16)                                                      */ \
  /*_(vqdmlal_laneq_s32)                                                      */ \
  /*_(vqdmlalh_laneq_s16)                                                     */ \
  /*_(vqdmlals_laneq_s32)                                                     */ \
  /*_(vqdmlal_high_laneq_s16)                                                 */ \
  /*_(vqdmlal_high_laneq_s32)                                                 */ \
  _(vmls_lane_s16)                                                               \
  _(vmls_lane_s32)                                                               \
  _(vmls_lane_f32)                                                               \
  _(vmls_lane_u16)                                                               \
  _(vmls_lane_u32)                                                               \
  _(vmlsq_lane_s16)                                                              \
  _(vmlsq_lane_s32)                                                              \
  _(vmlsq_lane_f32)                                                              \
  /*_(vmls_laneq_s16)                                                         */ \
  /*_(vmlsq_laneq_s16)                                                        */ \
  /*_(vmls_laneq_s32)                                                         */ \
  /*_(vmlsq_laneq_s32)                                                        */ \
  /*_(vmls_laneq_u16)                                                         */ \
  /*_(vmlsq_laneq_u16)                                                        */ \
  /*_(vmls_laneq_u32)                                                         */ \
  /*_(vmlsq_laneq_u32)                                                        */ \
  /*_(vmls_laneq_f32)                                                         */ \
  /*_(vmlsq_laneq_f32)                                                        */ \
  _(vmlsq_lane_u16)                                                              \
  _(vmlsq_lane_u32)                                                              \
  _(vmlsl_lane_s16)                                                              \
  _(vmlsl_lane_s32)                                                              \
  _(vmlsl_lane_u16)                                                              \
  _(vmlsl_lane_u32)                                                              \
  /*_(vmlsl_high_lane_s16)                                                    */ \
  /*_(vmlsl_high_lane_s32)                                                    */ \
  /*_(vmlsl_high_lane_u16)                                                    */ \
  /*_(vmlsl_high_lane_u32)                                                    */ \
  /*_(vmlsl_laneq_s16)                                                        */ \
  /*_(vmlsl_laneq_s32)                                                        */ \
  /*_(vmlsl_laneq_u16)                                                        */ \
  /*_(vmlsl_laneq_u32)                                                        */ \
  /*_(vmlsl_high_laneq_s16)                                                   */ \
  /*_(vmlsl_high_laneq_s32)                                                   */ \
  /*_(vmlsl_high_laneq_u16)                                                   */ \
  /*_(vmlsl_high_laneq_u32)                                                   */ \
  _(vqdmlsl_lane_s16)                                                            \
  _(vqdmlsl_lane_s32)                                                            \
  /*_(vqdmlslh_lane_s16)                                                      */ \
  /*_(vqdmlsls_lane_s32)                                                      */ \
  /*_(vqdmlsl_high_lane_s16)                                                  */ \
  /*_(vqdmlsl_high_lane_s32)                                                  */ \
  /*_(vqdmlsl_laneq_s16)                                                      */ \
  /*_(vqdmlsl_laneq_s32)                                                      */ \
  /*_(vqdmlslh_laneq_s16)                                                     */ \
  /*_(vqdmlsls_laneq_s32)                                                     */ \
  /*_(vqdmlsl_high_laneq_s16)                                                 */ \
  /*_(vqdmlsl_high_laneq_s32)                                                 */ \
  _(vmull_lane_s16)                                                              \
  _(vmull_lane_s32)                                                              \
  _(vmull_lane_u16)                                                              \
  _(vmull_lane_u32)                                                              \
  /*_(vmull_high_lane_s16)                                                    */ \
  /*_(vmull_high_lane_s32)                                                    */ \
  /*_(vmull_high_lane_u16)                                                    */ \
  /*_(vmull_high_lane_u32)                                                    */ \
  /*_(vmull_laneq_s16)                                                        */ \
  /*_(vmull_laneq_s32)                                                        */ \
  /*_(vmull_laneq_u16)                                                        */ \
  /*_(vmull_laneq_u32)                                                        */ \
  /*_(vmull_high_laneq_s16)                                                   */ \
  /*_(vmull_high_laneq_s32)                                                   */ \
  /*_(vmull_high_laneq_u16)                                                   */ \
  /*_(vmull_high_laneq_u32)                                                   */ \
  _(vqdmull_lane_s16)                                                            \
  _(vqdmull_lane_s32)                                                            \
  /*_(vqdmullh_lane_s16)                                                      */ \
  /*_(vqdmulls_lane_s32)                                                      */ \
  /*_(vqdmull_high_lane_s16)                                                  */ \
  /*_(vqdmull_high_lane_s32)                                                  */ \
  /*_(vqdmull_laneq_s16)                                                      */ \
  /*_(vqdmull_laneq_s32)                                                      */ \
  /*_(vqdmullh_laneq_s16)                                                     */ \
  /*_(vqdmulls_laneq_s32)                                                     */ \
  /*_(vqdmull_high_laneq_s16)                                                 */ \
  /*_(vqdmull_high_laneq_s32)                                                 */ \
  _(vqdmulhq_lane_s16)                                                           \
  _(vqdmulhq_lane_s32)                                                           \
  /*_(vqdmulhh_lane_s16)                                                      */ \
  /*_(vqdmulhs_lane_s32)                                                      */ \
  /*_(vqdmulh_laneq_s16)                                                      */ \
  /*_(vqdmulhq_laneq_s16)                                                     */ \
  /*_(vqdmulh_laneq_s32)                                                      */ \
  /*_(vqdmulhq_laneq_s32)                                                     */ \
  /*_(vqdmulhh_laneq_s16)                                                     */ \
  /*_(vqdmulhs_laneq_s32)                                                     */ \
  _(vqdmulh_lane_s16)                                                            \
  _(vqdmulh_lane_s32)                                                            \
  _(vqrdmulhq_lane_s16)                                                          \
  _(vqrdmulhq_lane_s32)                                                          \
  /*_(vqrdmulhh_lane_s16)                                                     */ \
  /*_(vqrdmulhs_lane_s32)                                                     */ \
  /*_(vqrdmulh_laneq_s16)                                                     */ \
  /*_(vqrdmulhq_laneq_s16)                                                    */ \
  /*_(vqrdmulh_laneq_s32)                                                     */ \
  /*_(vqrdmulhq_laneq_s32)                                                    */ \
  /*_(vqrdmulhh_laneq_s16)                                                    */ \
  /*_(vqrdmulhs_laneq_s32)                                                    */ \
  _(vqrdmulh_lane_s16)                                                           \
  _(vqrdmulh_lane_s32)                                                           \
  _(vqrdmlahq_lane_s16)                                                          \
  /*_(vqrdmlah_laneq_s16)                                                     */ \
  /*_(vqrdmlahq_laneq_s16)                                                    */ \
  _(vqrdmlahq_lane_s32)                                                          \
  /*_(vqrdmlah_laneq_s32)                                                     */ \
  /*_(vqrdmlahq_laneq_s32)                                                    */ \
  _(vqrdmlah_lane_s16)                                                           \
  _(vqrdmlah_lane_s32)                                                           \
  _(vqrdmlshq_lane_s16)                                                          \
  /*_(vqrdmlsh_laneq_s16)                                                     */ \
  /*_(vqrdmlshq_laneq_s16)                                                    */ \
  _(vqrdmlshq_lane_s32)                                                          \
  /*_(vqrdmlsh_laneq_s32)                                                     */ \
  /*_(vqrdmlshq_laneq_s32)                                                    */ \
  /*_(vqrdmlahh_s16)                                                          */ \
  /*_(vqrdmlahs_s32)                                                          */ \
  /*_(vqrdmlshh_s16)                                                          */ \
  /*_(vqrdmlshs_s32)                                                          */ \
  /*_(vqrdmlahh_lane_s16)                                                     */ \
  /*_(vqrdmlahh_laneq_s16)                                                    */ \
  /*_(vqrdmlahs_lane_s32)                                                     */ \
  /*_(vqrdmlahs_laneq_s32)                                                    */ \
  /*_(vqrdmlshh_lane_s16)                                                     */ \
  /*_(vqrdmlshh_laneq_s16)                                                    */ \
  /*_(vqrdmlshs_lane_s32)                                                     */ \
  /*_(vqrdmlshs_laneq_s32)                                                    */ \
  /*_(vabsh_f16)                                                              */ \
  /*_(vceqzh_f16)                                                             */ \
  /*_(vcgezh_f16)                                                             */ \
  /*_(vcgtzh_f16)                                                             */ \
  /*_(vclezh_f16)                                                             */ \
  /*_(vcltzh_f16)                                                             */ \
  /*_(vcvth_f16_s16)                                                          */ \
  /*_(vcvth_f16_s32)                                                          */ \
  /*_(vcvth_f16_s64)                                                          */ \
  /*_(vcvth_f16_u16)                                                          */ \
  /*_(vcvth_f16_u32)                                                          */ \
  /*_(vcvth_f16_u64)                                                          */ \
  /*_(vcvth_s16_f16)                                                          */ \
  /*_(vcvth_s32_f16)                                                          */ \
  /*_(vcvth_s64_f16)                                                          */ \
  /*_(vcvth_u16_f16)                                                          */ \
  /*_(vcvth_u32_f16)                                                          */ \
  /*_(vcvth_u64_f16)                                                          */ \
  /*_(vcvtah_s16_f16)                                                         */ \
  /*_(vcvtah_s32_f16)                                                         */ \
  /*_(vcvtah_s64_f16)                                                         */ \
  /*_(vcvtah_u16_f16)                                                         */ \
  /*_(vcvtah_u32_f16)                                                         */ \
  /*_(vcvtah_u64_f16)                                                         */ \
  /*_(vcvtmh_s16_f16)                                                         */ \
  /*_(vcvtmh_s32_f16)                                                         */ \
  /*_(vcvtmh_s64_f16)                                                         */ \
  /*_(vcvtmh_u16_f16)                                                         */ \
  /*_(vcvtmh_u32_f16)                                                         */ \
  /*_(vcvtmh_u64_f16)                                                         */ \
  /*_(vcvtnh_s16_f16)                                                         */ \
  /*_(vcvtnh_s32_f16)                                                         */ \
  /*_(vcvtnh_s64_f16)                                                         */ \
  /*_(vcvtnh_u16_f16)                                                         */ \
  /*_(vcvtnh_u32_f16)                                                         */ \
  /*_(vcvtnh_u64_f16)                                                         */ \
  /*_(vcvtph_s16_f16)                                                         */ \
  /*_(vcvtph_s32_f16)                                                         */ \
  /*_(vcvtph_s64_f16)                                                         */ \
  /*_(vcvtph_u16_f16)                                                         */ \
  /*_(vcvtph_u32_f16)                                                         */ \
  /*_(vcvtph_u64_f16)                                                         */ \
  /*_(vnegh_f16)                                                              */ \
  /*_(vrecpeh_f16)                                                            */ \
  /*_(vrecpxh_f16)                                                            */ \
  /*_(vrndh_f16)                                                              */ \
  /*_(vrndah_f16)                                                             */ \
  /*_(vrndih_f16)                                                             */ \
  /*_(vrndmh_f16)                                                             */ \
  /*_(vrndnh_f16)                                                             */ \
  /*_(vrndph_f16)                                                             */ \
  /*_(vrndxh_f16)                                                             */ \
  /*_(vrsqrteh_f16)                                                           */ \
  /*_(vsqrth_f16)                                                             */ \
  /*_(vaddh_f16)                                                              */ \
  /*_(vabdh_f16)                                                              */ \
  /*_(vcageh_f16)                                                             */ \
  /*_(vcagth_f16)                                                             */ \
  /*_(vcaleh_f16)                                                             */ \
  /*_(vcalth_f16)                                                             */ \
  /*_(vceqh_f16)                                                              */ \
  /*_(vcgeh_f16)                                                              */ \
  /*_(vcgth_f16)                                                              */ \
  /*_(vcleh_f16)                                                              */ \
  /*_(vclth_f16)                                                              */ \
  /*_(vcvth_n_f16_s16)                                                        */ \
  /*_(vcvth_n_f16_s32)                                                        */ \
  /*_(vcvth_n_f16_s64)                                                        */ \
  /*_(vcvth_n_f16_u16)                                                        */ \
  /*_(vcvth_n_f16_u32)                                                        */ \
  /*_(vcvth_n_f16_u64)                                                        */ \
  /*_(vcvth_n_s16_f16)                                                        */ \
  /*_(vcvth_n_s32_f16)                                                        */ \
  /*_(vcvth_n_s64_f16)                                                        */ \
  /*_(vcvth_n_u16_f16)                                                        */ \
  /*_(vcvth_n_u32_f16)                                                        */ \
  /*_(vcvth_n_u64_f16)                                                        */ \
  /*_(vdivh_f16)                                                              */ \
  /*_(vmaxh_f16)                                                              */ \
  /*_(vmaxnmh_f16)                                                            */ \
  /*_(vminh_f16)                                                              */ \
  /*_(vminnmh_f16)                                                            */ \
  /*_(vmulh_f16)                                                              */ \
  /*_(vmulxh_f16)                                                             */ \
  /*_(vrecpsh_f16)                                                            */ \
  /*_(vrsqrtsh_f16)                                                           */ \
  /*_(vsubh_f16)                                                              */ \
  /*_(vfmah_f16)                                                              */ \
  /*_(vfmsh_f16)                                                              */ \
  _(vqrdmlsh_lane_s16)                                                           \
  _(vqrdmlsh_lane_s32)                                                           \
  _(vmul_n_s16)                                                                  \
  _(vmul_n_s32)                                                                  \
  _(vmul_n_f32)                                                                  \
  _(vmul_n_u16)                                                                  \
  _(vmul_n_u32)                                                                  \
  _(vmulq_n_s16)                                                                 \
  _(vmulq_n_s32)                                                                 \
  _(vmulq_n_f32)                                                                 \
  /*_(vmul_n_f64)                                                             */ \
  /*_(vmulq_n_f64)                                                            */ \
  _(vmulq_n_u16)                                                                 \
  _(vmulq_n_u32)                                                                 \
  _(vmull_n_s16)                                                                 \
  _(vmull_n_s32)                                                                 \
  _(vmull_n_u16)                                                                 \
  _(vmull_n_u32)                                                                 \
  /*_(vmull_high_n_s16)                                                       */ \
  /*_(vmull_high_n_s32)                                                       */ \
  /*_(vmull_high_n_u16)                                                       */ \
  /*_(vmull_high_n_u32)                                                       */ \
  _(vqdmull_n_s16)                                                               \
  _(vqdmull_n_s32)                                                               \
  /*_(vqdmull_high_n_s16)                                                     */ \
  /*_(vqdmull_high_n_s32)                                                     */ \
  _(vqdmulhq_n_s16)                                                              \
  _(vqdmulhq_n_s32)                                                              \
  _(vqdmulh_n_s16)                                                               \
  _(vqdmulh_n_s32)                                                               \
  _(vqrdmulhq_n_s16)                                                             \
  _(vqrdmulhq_n_s32)                                                             \
  _(vqrdmulh_n_s16)                                                              \
  _(vqrdmulh_n_s32)                                                              \
  _(vmla_n_s16)                                                                  \
  _(vmla_n_s32)                                                                  \
  _(vmla_n_f32)                                                                  \
  _(vmla_n_u16)                                                                  \
  _(vmla_n_u32)                                                                  \
  _(vmlaq_n_s16)                                                                 \
  _(vmlaq_n_s32)                                                                 \
  _(vmlaq_n_f32)                                                                 \
  _(vmlaq_n_u16)                                                                 \
  _(vmlaq_n_u32)                                                                 \
  _(vmlal_n_s16)                                                                 \
  _(vmlal_n_s32)                                                                 \
  _(vmlal_n_u16)                                                                 \
  _(vmlal_n_u32)                                                                 \
  /*_(vmlal_high_n_s16)                                                       */ \
  /*_(vmlal_high_n_s32)                                                       */ \
  /*_(vmlal_high_n_u16)                                                       */ \
  /*_(vmlal_high_n_u32)                                                       */ \
  _(vqdmlal_n_s16)                                                               \
  _(vqdmlal_n_s32)                                                               \
  /*_(vqdmlal_high_n_s16)                                                     */ \
  /*_(vqdmlal_high_n_s32)                                                     */ \
  _(vmls_n_s16)                                                                  \
  _(vmls_n_s32)                                                                  \
  _(vmls_n_f32)                                                                  \
  _(vmls_n_u16)                                                                  \
  _(vmls_n_u32)                                                                  \
  _(vmlsq_n_s16)                                                                 \
  _(vmlsq_n_s32)                                                                 \
  _(vmlsq_n_f32)                                                                 \
  _(vmlsq_n_u16)                                                                 \
  _(vmlsq_n_u32)                                                                 \
  _(vmlsl_n_s16)                                                                 \
  _(vmlsl_n_s32)                                                                 \
  _(vmlsl_n_u16)                                                                 \
  _(vmlsl_n_u32)                                                                 \
  /*_(vmlsl_high_n_s16)                                                       */ \
  /*_(vmlsl_high_n_s32)                                                       */ \
  /*_(vmlsl_high_n_u16)                                                       */ \
  /*_(vmlsl_high_n_u32)                                                       */ \
  _(vqdmlsl_n_s16)                                                               \
  _(vqdmlsl_n_s32)                                                               \
  /*_(vqdmlsl_high_n_s16)                                                     */ \
  /*_(vqdmlsl_high_n_s32)                                                     */ \
  /*_(vext_p64)                                                          */      \
  _(vext_s8)                                                                     \
  _(vext_s16)                                                                    \
  _(vext_s32)                                                                    \
  _(vext_s64)                                                                    \
  _(vext_f32)                                                                    \
  _(vext_u8)                                                                     \
  _(vext_u16)                                                                    \
  _(vext_u32)                                                                    \
  _(vext_u64)                                                                    \
  /*_(vext_p8)                                                           */      \
  /*_(vext_p16)                                                          */      \
  /*_(vextq_p64)                                                         */      \
  _(vextq_s8)                                                                    \
  _(vextq_s16)                                                                   \
  _(vextq_s32)                                                                   \
  _(vextq_s64)                                                                   \
  _(vextq_f32)                                                                   \
  /*_(vext_f64)                                                               */ \
  /*_(vextq_f64)                                                              */ \
  _(vextq_u8)                                                                    \
  _(vextq_u16)                                                                   \
  _(vextq_u32)                                                                   \
  _(vextq_u64)                                                                   \
  /*_(vextq_p8)                                                          */      \
  /*_(vextq_p16)                                                         */      \
  _(vrev64_s8)                                                                   \
  _(vrev64_s16)                                                                  \
  _(vrev64_s32)                                                                  \
  _(vrev64_f32)                                                                  \
  _(vrev64_u8)                                                                   \
  _(vrev64_u16)                                                                  \
  _(vrev64_u32)                                                                  \
  /*_(vrev64_p8)                                                         */      \
  /*_(vrev64_p16)                                                        */      \
  _(vrev64q_s8)                                                                  \
  _(vrev64q_s16)                                                                 \
  _(vrev64q_s32)                                                                 \
  _(vrev64q_f32)                                                                 \
  _(vrev64q_u8)                                                                  \
  _(vrev64q_u16)                                                                 \
  _(vrev64q_u32)                                                                 \
  /*_(vrev64q_p8)                                                        */      \
  /*_(vrev64q_p16)                                                       */      \
  _(vrev32_s8)                                                                   \
  _(vrev32_s16)                                                                  \
  _(vrev32_u8)                                                                   \
  _(vrev32_u16)                                                                  \
  /*_(vrev32_p8)                                                         */      \
  /*_(vrev32_p16)                                                        */      \
  _(vrev32q_s8)                                                                  \
  _(vrev32q_s16)                                                                 \
  _(vrev32q_u8)                                                                  \
  _(vrev32q_u16)                                                                 \
  /*_(vrev32q_p8)                                                        */      \
  /*_(vrev32q_p16)                                                       */      \
  _(vrev16_s8)                                                                   \
  _(vrev16_u8)                                                                   \
  /*_(vrev16_p8)                                                         */      \
  _(vrev16q_s8)                                                                  \
  _(vrev16q_u8)                                                                  \
  /*_(vrev16q_p8)                                                        */      \
  /*_(vzip1_s8)                                                               */ \
  /*_(vzip1q_s8)                                                              */ \
  /*_(vzip1_s16)                                                              */ \
  /*_(vzip1q_s16)                                                             */ \
  /*_(vzip1_s32)                                                              */ \
  /*_(vzip1q_s32)                                                             */ \
  /*_(vzip1q_s64)                                                             */ \
  /*_(vzip1_u8)                                                               */ \
  /*_(vzip1q_u8)                                                              */ \
  /*_(vzip1_u16)                                                              */ \
  /*_(vzip1q_u16)                                                             */ \
  /*_(vzip1_u32)                                                              */ \
  /*_(vzip1q_u32)                                                             */ \
  /*_(vzip1q_u64)                                                             */ \
  /*_(vzip1q_p64)                                                             */ \
  /*_(vzip1_f32)                                                              */ \
  /*_(vzip1q_f32)                                                             */ \
  /*_(vzip1q_f64)                                                             */ \
  /*_(vzip1_p8)                                                               */ \
  /*_(vzip1q_p8)                                                              */ \
  /*_(vzip1_p16)                                                              */ \
  /*_(vzip1q_p16)                                                             */ \
  /*_(vzip2_s8)                                                               */ \
  /*_(vzip2q_s8)                                                              */ \
  /*_(vzip2_s16)                                                              */ \
  /*_(vzip2q_s16)                                                             */ \
  /*_(vzip2_s32)                                                              */ \
  /*_(vzip2q_s32)                                                             */ \
  /*_(vzip2q_s64)                                                             */ \
  /*_(vzip2_u8)                                                               */ \
  /*_(vzip2q_u8)                                                              */ \
  /*_(vzip2_u16)                                                              */ \
  /*_(vzip2q_u16)                                                             */ \
  /*_(vzip2_u32)                                                              */ \
  /*_(vzip2q_u32)                                                             */ \
  /*_(vzip2q_u64)                                                             */ \
  /*_(vzip2q_p64)                                                             */ \
  /*_(vzip2_f32)                                                              */ \
  /*_(vzip2q_f32)                                                             */ \
  /*_(vzip2q_f64)                                                             */ \
  /*_(vzip2_p8)                                                               */ \
  /*_(vzip2q_p8)                                                              */ \
  /*_(vzip2_p16)                                                              */ \
  /*_(vzip2q_p16)                                                             */ \
  /*_(vuzp1_s8)                                                               */ \
  /*_(vuzp1q_s8)                                                              */ \
  /*_(vuzp1_s16)                                                              */ \
  /*_(vuzp1q_s16)                                                             */ \
  /*_(vuzp1_s32)                                                              */ \
  /*_(vuzp1q_s32)                                                             */ \
  /*_(vuzp1q_s64)                                                             */ \
  /*_(vuzp1_u8)                                                               */ \
  /*_(vuzp1q_u8)                                                              */ \
  /*_(vuzp1_u16)                                                              */ \
  /*_(vuzp1q_u16)                                                             */ \
  /*_(vuzp1_u32)                                                              */ \
  /*_(vuzp1q_u32)                                                             */ \
  /*_(vuzp1q_u64)                                                             */ \
  /*_(vuzp1q_p64)                                                             */ \
  /*_(vuzp1_f32)                                                              */ \
  /*_(vuzp1q_f32)                                                             */ \
  /*_(vuzp1q_f64)                                                             */ \
  /*_(vuzp1_p8)                                                               */ \
  /*_(vuzp1q_p8)                                                              */ \
  /*_(vuzp1_p16)                                                              */ \
  /*_(vuzp1q_p16)                                                             */ \
  /*_(vuzp2_s8)                                                               */ \
  /*_(vuzp2q_s8)                                                              */ \
  /*_(vuzp2_s16)                                                              */ \
  /*_(vuzp2q_s16)                                                             */ \
  /*_(vuzp2_s32)                                                              */ \
  /*_(vuzp2q_s32)                                                             */ \
  /*_(vuzp2q_s64)                                                             */ \
  /*_(vuzp2_u8)                                                               */ \
  /*_(vuzp2q_u8)                                                              */ \
  /*_(vuzp2_u16)                                                              */ \
  /*_(vuzp2q_u16)                                                             */ \
  /*_(vuzp2_u32)                                                              */ \
  /*_(vuzp2q_u32)                                                             */ \
  /*_(vuzp2q_u64)                                                             */ \
  /*_(vuzp2q_p64)                                                             */ \
  /*_(vuzp2_f32)                                                              */ \
  /*_(vuzp2q_f32)                                                             */ \
  /*_(vuzp2q_f64)                                                             */ \
  /*_(vuzp2_p8)                                                               */ \
  /*_(vuzp2q_p8)                                                              */ \
  /*_(vuzp2_p16)                                                              */ \
  /*_(vuzp2q_p16)                                                             */ \
  /*_(vtrn1_s8)                                                               */ \
  /*_(vtrn1q_s8)                                                              */ \
  /*_(vtrn1_s16)                                                              */ \
  /*_(vtrn1q_s16)                                                             */ \
  /*_(vtrn1_s32)                                                              */ \
  /*_(vtrn1q_s32)                                                             */ \
  /*_(vtrn1q_s64)                                                             */ \
  /*_(vtrn1_u8)                                                               */ \
  /*_(vtrn1q_u8)                                                              */ \
  /*_(vtrn1_u16)                                                              */ \
  /*_(vtrn1q_u16)                                                             */ \
  /*_(vtrn1_u32)                                                              */ \
  /*_(vtrn1q_u32)                                                             */ \
  /*_(vtrn1q_u64)                                                             */ \
  /*_(vtrn1q_p64)                                                             */ \
  /*_(vtrn1_f32)                                                              */ \
  /*_(vtrn1q_f32)                                                             */ \
  /*_(vtrn1q_f64)                                                             */ \
  /*_(vtrn1_p8)                                                               */ \
  /*_(vtrn1q_p8)                                                              */ \
  /*_(vtrn1_p16)                                                              */ \
  /*_(vtrn1q_p16)                                                             */ \
  /*_(vtrn2_s8)                                                               */ \
  /*_(vtrn2q_s8)                                                              */ \
  /*_(vtrn2_s16)                                                              */ \
  /*_(vtrn2q_s16)                                                             */ \
  /*_(vtrn2_s32)                                                              */ \
  /*_(vtrn2q_s32)                                                             */ \
  /*_(vtrn2q_s64)                                                             */ \
  /*_(vtrn2_u8)                                                               */ \
  /*_(vtrn2q_u8)                                                              */ \
  /*_(vtrn2_u16)                                                              */ \
  /*_(vtrn2q_u16)                                                             */ \
  /*_(vtrn2_u32)                                                              */ \
  /*_(vtrn2q_u32)                                                             */ \
  /*_(vtrn2q_u64)                                                             */ \
  /*_(vtrn2q_p64)                                                             */ \
  /*_(vtrn2_f32)                                                              */ \
  /*_(vtrn2q_f32)                                                             */ \
  /*_(vtrn2q_f64)                                                             */ \
  /*_(vtrn2_p8)                                                               */ \
  /*_(vtrn2q_p8)                                                              */ \
  /*_(vtrn2_p16)                                                              */ \
  /*_(vtrn2q_p16)                                                             */ \
  /*_(vbsl_p64)                                                          */      \
  _(vbsl_s8)                                                                     \
  _(vbsl_s16)                                                                    \
  _(vbsl_s32)                                                                    \
  _(vbsl_s64)                                                                    \
  _(vbsl_f32)                                                                    \
  _(vbsl_u8)                                                                     \
  _(vbsl_u16)                                                                    \
  _(vbsl_u32)                                                                    \
  _(vbsl_u64)                                                                    \
  /*_(vbsl_p8)                                                           */      \
  /*_(vbsl_p16)                                                          */      \
  /*_(vbslq_p64)                                                         */      \
  _(vbslq_s8)                                                                    \
  _(vbslq_s16)                                                                   \
  _(vbslq_s32)                                                                   \
  _(vbslq_s64)                                                                   \
  _(vbslq_f32)                                                                   \
  _(vbslq_u8)                                                                    \
  _(vbslq_u16)                                                                   \
  _(vbslq_u32)                                                                   \
  _(vbslq_u64)                                                                   \
  /*_(vbslq_p8)                                                          */      \
  /*_(vbslq_p16)                                                         */      \
  /*_(vbsl_f64)                                                               */ \
  /*_(vbslq_f64)                                                              */ \
  /*_(vcopy_lane_s8)                                                          */ \
  /*_(vcopyq_lane_s8)                                                         */ \
  /*_(vcopy_lane_s16)                                                         */ \
  /*_(vcopyq_lane_s16)                                                        */ \
  /*_(vcopy_lane_s32)                                                         */ \
  /*_(vcopyq_lane_s32)                                                        */ \
  /*_(vcopy_lane_s64)                                                         */ \
  /*_(vcopyq_lane_s64)                                                        */ \
  /*_(vcopy_lane_u8)                                                          */ \
  /*_(vcopyq_lane_u8)                                                         */ \
  /*_(vcopy_lane_u16)                                                         */ \
  /*_(vcopyq_lane_u16)                                                        */ \
  /*_(vcopy_lane_u32)                                                         */ \
  /*_(vcopyq_lane_u32)                                                        */ \
  /*_(vcopy_lane_u64)                                                         */ \
  /*_(vcopyq_lane_u64)                                                        */ \
  /*_(vcopy_lane_p64)                                                         */ \
  /*_(vcopyq_lane_p64)                                                        */ \
  /*_(vcopy_lane_f32)                                                         */ \
  /*_(vcopyq_lane_f32)                                                        */ \
  /*_(vcopy_lane_f64)                                                         */ \
  /*_(vcopyq_lane_f64)                                                        */ \
  /*_(vcopy_lane_p8)                                                          */ \
  /*_(vcopyq_lane_p8)                                                         */ \
  /*_(vcopy_lane_p16)                                                         */ \
  /*_(vcopyq_lane_p16)                                                        */ \
  /*_(vcopy_laneq_s8)                                                         */ \
  /*_(vcopyq_laneq_s8)                                                        */ \
  /*_(vcopy_laneq_s16)                                                        */ \
  /*_(vcopyq_laneq_s16)                                                       */ \
  /*_(vcopy_laneq_s32)                                                        */ \
  /*_(vcopyq_laneq_s32)                                                       */ \
  /*_(vcopy_laneq_s64)                                                        */ \
  /*_(vcopyq_laneq_s64)                                                       */ \
  /*_(vcopy_laneq_u8)                                                         */ \
  /*_(vcopyq_laneq_u8)                                                        */ \
  /*_(vcopy_laneq_u16)                                                        */ \
  /*_(vcopyq_laneq_u16)                                                       */ \
  /*_(vcopy_laneq_u32)                                                        */ \
  /*_(vcopyq_laneq_u32)                                                       */ \
  /*_(vcopy_laneq_u64)                                                        */ \
  /*_(vcopyq_laneq_u64)                                                       */ \
  /*_(vcopy_laneq_p64)                                                        */ \
  /*_(vcopyq_laneq_p64)                                                       */ \
  /*_(vcopy_laneq_f32)                                                        */ \
  /*_(vcopyq_laneq_f32)                                                       */ \
  /*_(vcopy_laneq_f64)                                                        */ \
  /*_(vcopyq_laneq_f64)                                                       */ \
  /*_(vcopy_laneq_p8)                                                         */ \
  /*_(vcopyq_laneq_p8)                                                        */ \
  /*_(vcopy_laneq_p16)                                                        */ \
  /*_(vcopyq_laneq_p16)                                                       */ \
  /*_(vrbit_s8)                                                               */ \
  /*_(vrbitq_s8)                                                              */ \
  /*_(vrbit_u8)                                                               */ \
  /*_(vrbitq_u8)                                                              */ \
  /*_(vrbit_p8)                                                               */ \
  /*_(vrbitq_p8)                                                              */ \
  _(vtrn_s8)                                                                     \
  _(vtrn_s16)                                                                    \
  _(vtrn_u8)                                                                     \
  _(vtrn_u16)                                                                    \
  /*_(vtrn_p8)                                                           */      \
  /*_(vtrn_p16)                                                          */      \
  _(vtrn_s32)                                                                    \
  _(vtrn_f32)                                                                    \
  _(vtrn_u32)                                                                    \
  _(vtrnq_s8)                                                                    \
  _(vtrnq_s16)                                                                   \
  _(vtrnq_s32)                                                                   \
  _(vtrnq_f32)                                                                   \
  _(vtrnq_u8)                                                                    \
  _(vtrnq_u16)                                                                   \
  _(vtrnq_u32)                                                                   \
  /*_(vtrnq_p8)                                                          */      \
  /*_(vtrnq_p16)                                                         */      \
  _(vzip_s8)                                                                     \
  _(vzip_s16)                                                                    \
  _(vzip_u8)                                                                     \
  _(vzip_u16)                                                                    \
  /*_(vzip_p8)                                                           */      \
  /*_(vzip_p16)                                                          */      \
  _(vzip_s32)                                                                    \
  _(vzip_f32)                                                                    \
  _(vzip_u32)                                                                    \
  _(vzipq_s8)                                                                    \
  _(vzipq_s16)                                                                   \
  _(vzipq_s32)                                                                   \
  _(vzipq_f32)                                                                   \
  _(vzipq_u8)                                                                    \
  _(vzipq_u16)                                                                   \
  _(vzipq_u32)                                                                   \
  /*_(vzipq_p8)                                                          */      \
  /*_(vzipq_p16)                                                         */      \
  _(vuzp_s8)                                                                     \
  _(vuzp_s16)                                                                    \
  _(vuzp_s32)                                                                    \
  _(vuzp_f32)                                                                    \
  _(vuzp_u8)                                                                     \
  _(vuzp_u16)                                                                    \
  _(vuzp_u32)                                                                    \
  /*_(vuzp_p8)                                                           */      \
  /*_(vuzp_p16)                                                          */      \
  _(vuzpq_s8)                                                                    \
  _(vuzpq_s16)                                                                   \
  _(vuzpq_s32)                                                                   \
  _(vuzpq_f32)                                                                   \
  _(vuzpq_u8)                                                                    \
  _(vuzpq_u16)                                                                   \
  _(vuzpq_u32)                                                                   \
  /*_(vuzpq_p8)                                                          */      \
  /*_(vuzpq_p16)                                                         */      \
  /*_(vld1_p64)                                                          */      \
  _(vld1_s8)                                                                     \
  _(vld1_s16)                                                                    \
  _(vld1_s32)                                                                    \
  _(vld1_s64)                                                                    \
  /*_(vld1_f16)                                                          */      \
  _(vld1_f32)                                                                    \
  _(vld1_u8)                                                                     \
  _(vld1_u16)                                                                    \
  _(vld1_u32)                                                                    \
  _(vld1_u64)                                                                    \
  /*_(vld1_p8)                                                           */      \
  /*_(vld1_p16)                                                          */      \
  /*_(vld1q_p64)                                                         */      \
  _(vld1q_s8)                                                                    \
  _(vld1q_s16)                                                                   \
  _(vld1q_s32)                                                                   \
  _(vld1q_s64)                                                                   \
  /*_(vld1q_f16)                                                         */      \
  _(vld1q_f32)                                                                   \
  _(vld1q_u8)                                                                    \
  _(vld1q_u16)                                                                   \
  _(vld1q_u32)                                                                   \
  _(vld1q_u64)                                                                   \
  /*_(vld1q_p8)                                                          */      \
  /*_(vld1q_p16)                                                         */      \
  _(vld1_f64)                                                                    \
  _(vld1q_f64)                                                                   \
  _(vld1_lane_s8)                                                                \
  _(vld1_lane_s16)                                                               \
  _(vld1_lane_s32)                                                               \
  /*_(vld1_lane_f16)                                                     */      \
  _(vld1_lane_f32)                                                               \
  _(vld1_lane_u8)                                                                \
  _(vld1_lane_u16)                                                               \
  _(vld1_lane_u32)                                                               \
  /*_(vld1_lane_p8)                                                      */      \
  /*_(vld1_lane_p16)                                                     */      \
  /*_(vld1_lane_p64)                                                     */      \
  _(vld1_lane_s64)                                                               \
  _(vld1_lane_u64)                                                               \
  _(vld1q_lane_s8)                                                               \
  _(vld1q_lane_s16)                                                              \
  _(vld1q_lane_s32)                                                              \
  /*_(vld1q_lane_f16)                                                    */      \
  _(vld1q_lane_f32)                                                              \
  _(vld1q_lane_u8)                                                               \
  _(vld1q_lane_u16)                                                              \
  _(vld1q_lane_u32)                                                              \
  /*_(vld1q_lane_p8)                                                     */      \
  /*_(vld1q_lane_p16)                                                    */      \
  /*_(vld1_lane_f64)                                                          */ \
  /*_(vld1q_lane_f64)                                                         */ \
  /*_(vld1q_lane_p64)                                                    */      \
  _(vld1q_lane_s64)                                                              \
  _(vld1q_lane_u64)                                                              \
  _(vld1_dup_s8)                                                                 \
  _(vld1_dup_s16)                                                                \
  _(vld1_dup_s32)                                                                \
  /*_(vld1_dup_f16)                                                      */      \
  _(vld1_dup_f32)                                                                \
  _(vld1_dup_u8)                                                                 \
  _(vld1_dup_u16)                                                                \
  _(vld1_dup_u32)                                                                \
  /*_(vld1_dup_p8)                                                       */      \
  /*_(vld1_dup_p16)                                                      */      \
  /*_(vld1_dup_p64)                                                      */      \
  _(vld1_dup_s64)                                                                \
  _(vld1_dup_u64)                                                                \
  _(vld1q_dup_s8)                                                                \
  _(vld1q_dup_s16)                                                               \
  _(vld1q_dup_s32)                                                               \
  /*_(vld1q_dup_f16)                                                     */      \
  _(vld1q_dup_f32)                                                               \
  _(vld1q_dup_u8)                                                                \
  _(vld1q_dup_u16)                                                               \
  _(vld1q_dup_u32)                                                               \
  /*_(vld1q_dup_p8)                                                      */      \
  /*_(vld1q_dup_p16)                                                     */      \
  /*_(vld1_dup_f64)                                                           */ \
  /*_(vld1q_dup_f64)                                                          */ \
  /*_(vld1q_dup_p64)                                                     */      \
  _(vld1q_dup_s64)                                                               \
  _(vld1q_dup_u64)                                                               \
  /*_(vst1_p64)                                                          */      \
  _(vst1_s8)                                                                     \
  _(vst1_s16)                                                                    \
  _(vst1_s32)                                                                    \
  _(vst1_s64)                                                                    \
  /*_(vst1_f16)                                                          */      \
  _(vst1_f32)                                                                    \
  _(vst1_u8)                                                                     \
  _(vst1_u16)                                                                    \
  _(vst1_u32)                                                                    \
  _(vst1_u64)                                                                    \
  /*_(vst1_p8)                                                           */      \
  /*_(vst1_p16)                                                          */      \
  /*_(vst1q_p64)                                                         */      \
  _(vst1q_s8)                                                                    \
  _(vst1q_s16)                                                                   \
  _(vst1q_s32)                                                                   \
  _(vst1q_s64)                                                                   \
  /*_(vst1q_f16)                                                         */      \
  _(vst1q_f32)                                                                   \
  _(vst1q_u8)                                                                    \
  _(vst1q_u16)                                                                   \
  _(vst1q_u32)                                                                   \
  _(vst1q_u64)                                                                   \
  /*_(vst1q_p8)                                                          */      \
  /*_(vst1q_p16)                                                         */      \
  /*_(vst1_f64)                                                               */ \
  /*_(vst1q_f64)                                                              */ \
  _(vst1_lane_s8)                                                                \
  _(vst1_lane_s16)                                                               \
  _(vst1_lane_s32)                                                               \
  /*_(vst1_lane_f16)                                                     */      \
  _(vst1_lane_f32)                                                               \
  _(vst1_lane_u8)                                                                \
  _(vst1_lane_u16)                                                               \
  _(vst1_lane_u32)                                                               \
  /*_(vst1_lane_p8)                                                      */      \
  /*_(vst1_lane_p16)                                                     */      \
  /*_(vst1_lane_p64)                                                     */      \
  _(vst1_lane_s64)                                                               \
  _(vst1_lane_u64)                                                               \
  _(vst1q_lane_s8)                                                               \
  _(vst1q_lane_s16)                                                              \
  _(vst1q_lane_s32)                                                              \
  /*_(vst1q_lane_f16)                                                    */      \
  _(vst1q_lane_f32)                                                              \
  _(vst1q_lane_u8)                                                               \
  _(vst1q_lane_u16)                                                              \
  _(vst1q_lane_u32)                                                              \
  /*_(vst1q_lane_p8)                                                     */      \
  /*_(vst1q_lane_p16)                                                    */      \
  /*_(vst1_lane_f64)                                                          */ \
  /*_(vst1q_lane_f64)                                                         */ \
  /*_(vst1q_lane_p64)                                                    */      \
  _(vst1q_lane_s64)                                                              \
  _(vst1q_lane_u64)                                                              \
  _(vld2_s8)                                                                     \
  _(vld2_s16)                                                                    \
  _(vld2_s32)                                                                    \
  /*_(vld2_f16)                                                          */      \
  _(vld2_f32)                                                                    \
  _(vld2_u8)                                                                     \
  _(vld2_u16)                                                                    \
  _(vld2_u32)                                                                    \
  /*_(vld2_p8)                                                           */      \
  /*_(vld2_p16)                                                          */      \
  /*_(vld2_p64)                                                          */      \
  /*_(vld2q_s64)                                                              */ \
  /*_(vld2q_u64)                                                              */ \
  /*_(vld2q_p64)                                                              */ \
  /*_(vld2_f64)                                                               */ \
  /*_(vld2q_f64)                                                              */ \
  _(vld2_s64)                                                                    \
  _(vld2_u64)                                                                    \
  _(vld2q_s8)                                                                    \
  _(vld2q_s16)                                                                   \
  _(vld2q_s32)                                                                   \
  /*_(vld2q_f16)                                                         */      \
  _(vld2q_f32)                                                                   \
  _(vld2q_u8)                                                                    \
  _(vld2q_u16)                                                                   \
  _(vld2q_u32)                                                                   \
  /*_(vld2q_p8)                                                          */      \
  /*_(vld2q_p16)                                                         */      \
  _(vld2_lane_s8)                                                                \
  _(vld2_lane_s16)                                                               \
  _(vld2_lane_s32)                                                               \
  /*_(vld2_lane_f16)                                                     */      \
  _(vld2_lane_f32)                                                               \
  _(vld2_lane_u8)                                                                \
  _(vld2_lane_u16)                                                               \
  _(vld2_lane_u32)                                                               \
  /*_(vld2_lane_p8)                                                      */      \
  /*_(vld2q_lane_s8)                                                          */ \
  /*_(vld2q_lane_u8)                                                          */ \
  /*_(vld2q_lane_p8)                                                          */ \
  /*_(vld2_lane_s64)                                                          */ \
  /*_(vld2q_lane_s64)                                                         */ \
  /*_(vld2_lane_u64)                                                          */ \
  /*_(vld2q_lane_u64)                                                         */ \
  /*_(vld2_lane_p64)                                                          */ \
  /*_(vld2q_lane_p64)                                                         */ \
  /*_(vld2_lane_f64)                                                          */ \
  /*_(vld2q_lane_f64)                                                         */ \
  /*_(vld2_lane_p16)                                                     */      \
  _(vld2q_lane_s16)                                                              \
  _(vld2q_lane_s32)                                                              \
  /*_(vld2q_lane_f16)                                                    */      \
  _(vld2q_lane_f32)                                                              \
  _(vld2q_lane_u16)                                                              \
  _(vld2q_lane_u32)                                                              \
  /*_(vld2q_lane_p16)                                                    */      \
  _(vld2_dup_s8)                                                                 \
  /*_(vld2q_dup_s8)                                                           */ \
  _(vld2_dup_s16)                                                                \
  /*_(vld2q_dup_s16)                                                          */ \
  _(vld2_dup_s32)                                                                \
  /*_(vld2q_dup_s32)                                                          */ \
  /*_(vld2_dup_f16)                                                      */      \
  /*_(vld2q_dup_f16)                                                          */ \
  _(vld2_dup_f32)                                                                \
  /*_(vld2q_dup_f32)                                                          */ \
  _(vld2_dup_u8)                                                                 \
  /*_(vld2q_dup_u8)                                                           */ \
  _(vld2_dup_u16)                                                                \
  /*_(vld2q_dup_u16)                                                          */ \
  _(vld2_dup_u32)                                                                \
  /*_(vld2q_dup_u32)                                                          */ \
  /*_(vld2_dup_p8)                                                       */      \
  /*_(vld2q_dup_p8)                                                           */ \
  /*_(vld2_dup_p16)                                                      */      \
  /*_(vld2q_dup_p16)                                                          */ \
  /*_(vld2_dup_p64)                                                      */      \
  /*_(vld2q_dup_s64)                                                          */ \
  /*_(vld2q_dup_u64)                                                          */ \
  /*_(vld2q_dup_p64)                                                          */ \
  /*_(vld2_dup_f64)                                                           */ \
  /*_(vld2q_dup_f64)                                                          */ \
  _(vld2_dup_s64)                                                                \
  _(vld2_dup_u64)                                                                \
  _(vst2_s8)                                                                     \
  _(vst2_s16)                                                                    \
  _(vst2_s32)                                                                    \
  /*_(vst2_f16)                                                          */      \
  _(vst2_f32)                                                                    \
  _(vst2_u8)                                                                     \
  _(vst2_u16)                                                                    \
  _(vst2_u32)                                                                    \
  /*_(vst2_p8)                                                           */      \
  /*_(vst2_p16)                                                          */      \
  /*_(vst2_p64)                                                          */      \
  /*_(vst2q_s64)                                                              */ \
  /*_(vst2q_u64)                                                              */ \
  /*_(vst2q_p64)                                                              */ \
  /*_(vst2_f64)                                                               */ \
  /*_(vst2q_f64)                                                              */ \
  _(vst2_s64)                                                                    \
  _(vst2_u64)                                                                    \
  _(vst2q_s8)                                                                    \
  _(vst2q_s16)                                                                   \
  _(vst2q_s32)                                                                   \
  /*_(vst2q_f16)                                                         */      \
  _(vst2q_f32)                                                                   \
  _(vst2q_u8)                                                                    \
  _(vst2q_u16)                                                                   \
  _(vst2q_u32)                                                                   \
  /*_(vst2q_p8)                                                          */      \
  /*_(vst2q_p16)                                                         */      \
  _(vst2_lane_s8)                                                                \
  _(vst2_lane_s16)                                                               \
  _(vst2_lane_s32)                                                               \
  /*_(vst2_lane_f16)                                                     */      \
  _(vst2_lane_f32)                                                               \
  _(vst2_lane_u8)                                                                \
  _(vst2_lane_u16)                                                               \
  _(vst2_lane_u32)                                                               \
  /*_(vst2_lane_p8)                                                      */      \
  /*_(vst2_lane_p16)                                                     */      \
  _(vst2q_lane_s16)                                                              \
  _(vst2q_lane_s32)                                                              \
  /*_(vst2q_lane_f16)                                                    */      \
  _(vst2q_lane_f32)                                                              \
  _(vst2q_lane_u16)                                                              \
  _(vst2q_lane_u32)                                                              \
  /*_(vst2q_lane_p16)                                                    */      \
  /*_(vst2q_lane_s8)                                                          */ \
  /*_(vst2q_lane_u8)                                                          */ \
  /*_(vst2q_lane_p8)                                                          */ \
  /*_(vst2_lane_s64)                                                          */ \
  /*_(vst2q_lane_s64)                                                         */ \
  /*_(vst2_lane_u64)                                                          */ \
  /*_(vst2q_lane_u64)                                                         */ \
  /*_(vst2_lane_p64)                                                          */ \
  /*_(vst2q_lane_p64)                                                         */ \
  /*_(vst2_lane_f64)                                                          */ \
  /*_(vst2q_lane_f64)                                                         */ \
  _(vld3_s8)                                                                     \
  _(vld3_s16)                                                                    \
  _(vld3_s32)                                                                    \
  /*_(vld3_f16)                                                          */      \
  _(vld3_f32)                                                                    \
  _(vld3_u8)                                                                     \
  _(vld3_u16)                                                                    \
  _(vld3_u32)                                                                    \
  /*_(vld3_p8)                                                           */      \
  /*_(vld3_p16)                                                          */      \
  /*_(vld3_p64)                                                          */      \
  /*_(vld3q_s64)                                                              */ \
  /*_(vld3q_u64)                                                              */ \
  /*_(vld3q_p64)                                                              */ \
  /*_(vld3_f64)                                                               */ \
  /*_(vld3q_f64)                                                              */ \
  _(vld3_s64)                                                                    \
  _(vld3_u64)                                                                    \
  _(vld3q_s8)                                                                    \
  _(vld3q_s16)                                                                   \
  _(vld3q_s32)                                                                   \
  /*_(vld3q_f16)                                                         */      \
  _(vld3q_f32)                                                                   \
  _(vld3q_u8)                                                                    \
  _(vld3q_u16)                                                                   \
  _(vld3q_u32)                                                                   \
  /*_(vld3q_p8)                                                          */      \
  /*_(vld3q_p16)                                                         */      \
  _(vld3_lane_s8)                                                                \
  _(vld3_lane_s16)                                                               \
  _(vld3_lane_s32)                                                               \
  /*_(vld3_lane_f16)                                                     */      \
  _(vld3_lane_f32)                                                               \
  _(vld3_lane_u8)                                                                \
  _(vld3_lane_u16)                                                               \
  _(vld3_lane_u32)                                                               \
  /*_(vld3_lane_p8)                                                      */      \
  /*_(vld3q_lane_s8)                                                          */ \
  /*_(vld3q_lane_u8)                                                          */ \
  /*_(vld3q_lane_p8)                                                          */ \
  /*_(vld3_lane_s64)                                                          */ \
  /*_(vld3q_lane_s64)                                                         */ \
  /*_(vld3_lane_u64)                                                          */ \
  /*_(vld3q_lane_u64)                                                         */ \
  /*_(vld3_lane_p64)                                                          */ \
  /*_(vld3q_lane_p64)                                                         */ \
  /*_(vld3_lane_f64)                                                          */ \
  /*_(vld3q_lane_f64)                                                         */ \
  /*_(vld3_lane_p16)                                                     */      \
  _(vld3q_lane_s16)                                                              \
  _(vld3q_lane_s32)                                                              \
  /*_(vld3q_lane_f16)                                                    */      \
  _(vld3q_lane_f32)                                                              \
  _(vld3q_lane_u16)                                                              \
  _(vld3q_lane_u32)                                                              \
  /*_(vld3q_lane_p16)                                                    */      \
  _(vld3_dup_s8)                                                                 \
  /*_(vld3q_dup_s8)                                                           */ \
  _(vld3_dup_s16)                                                                \
  /*_(vld3q_dup_s16)                                                          */ \
  _(vld3_dup_s32)                                                                \
  /*_(vld3q_dup_s32)                                                          */ \
  /*_(vld3_dup_f16)                                                      */      \
  /*_(vld3q_dup_f16)                                                          */ \
  _(vld3_dup_f32)                                                                \
  /*_(vld3q_dup_f32)                                                          */ \
  _(vld3_dup_u8)                                                                 \
  /*_(vld3q_dup_u8)                                                           */ \
  _(vld3_dup_u16)                                                                \
  /*_(vld3q_dup_u16)                                                          */ \
  _(vld3_dup_u32)                                                                \
  /*_(vld3q_dup_u32)                                                          */ \
  /*_(vld3_dup_p8)                                                       */      \
  /*_(vld3q_dup_p8)                                                           */ \
  /*_(vld3_dup_p16)                                                      */      \
  /*_(vld3q_dup_p16)                                                          */ \
  /*_(vld3_dup_p64)                                                      */      \
  /*_(vld3q_dup_s64)                                                          */ \
  /*_(vld3q_dup_u64)                                                          */ \
  /*_(vld3q_dup_p64)                                                          */ \
  /*_(vld3_dup_f64)                                                           */ \
  /*_(vld3q_dup_f64)                                                          */ \
  _(vld3_dup_s64)                                                                \
  _(vld3_dup_u64)                                                                \
  _(vst3_s8)                                                                     \
  _(vst3_s16)                                                                    \
  _(vst3_s32)                                                                    \
  /*_(vst3_f16)                                                          */      \
  _(vst3_f32)                                                                    \
  _(vst3_u8)                                                                     \
  _(vst3_u16)                                                                    \
  _(vst3_u32)                                                                    \
  /*_(vst3_p8)                                                           */      \
  /*_(vst3_p16)                                                          */      \
  /*_(vst3_p64)                                                          */      \
  /*_(vst3q_s64)                                                              */ \
  /*_(vst3q_u64)                                                              */ \
  /*_(vst3q_p64)                                                              */ \
  /*_(vst3_f64)                                                               */ \
  /*_(vst3q_f64)                                                              */ \
  _(vst3_s64)                                                                    \
  _(vst3_u64)                                                                    \
  _(vst3q_s8)                                                                    \
  _(vst3q_s16)                                                                   \
  _(vst3q_s32)                                                                   \
  /*_(vst3q_f16)                                                         */      \
  _(vst3q_f32)                                                                   \
  _(vst3q_u8)                                                                    \
  _(vst3q_u16)                                                                   \
  _(vst3q_u32)                                                                   \
  /*_(vst3q_p8)                                                          */      \
  /*_(vst3q_p16)                                                         */      \
  _(vst3_lane_s8)                                                                \
  _(vst3_lane_s16)                                                               \
  _(vst3_lane_s32)                                                               \
  /*_(vst3_lane_f16)                                                     */      \
  _(vst3_lane_f32)                                                               \
  _(vst3_lane_u8)                                                                \
  _(vst3_lane_u16)                                                               \
  _(vst3_lane_u32)                                                               \
  /*_(vst3_lane_p8)                                                      */      \
  /*_(vst3_lane_p16)                                                     */      \
  _(vst3q_lane_s16)                                                              \
  _(vst3q_lane_s32)                                                              \
  /*_(vst3q_lane_f16)                                                    */      \
  _(vst3q_lane_f32)                                                              \
  _(vst3q_lane_u16)                                                              \
  _(vst3q_lane_u32)                                                              \
  /*_(vst3q_lane_p16)                                                    */      \
  /*_(vst3q_lane_s8)                                                          */ \
  /*_(vst3q_lane_u8)                                                          */ \
  /*_(vst3q_lane_p8)                                                          */ \
  /*_(vst3_lane_s64)                                                          */ \
  /*_(vst3q_lane_s64)                                                         */ \
  /*_(vst3_lane_u64)                                                          */ \
  /*_(vst3q_lane_u64)                                                         */ \
  /*_(vst3_lane_p64)                                                          */ \
  /*_(vst3q_lane_p64)                                                         */ \
  /*_(vst3_lane_f64)                                                          */ \
  /*_(vst3q_lane_f64)                                                         */ \
  _(vld4_s8)                                                                     \
  _(vld4_s16)                                                                    \
  _(vld4_s32)                                                                    \
  /*_(vld4_f16)                                                          */      \
  _(vld4_f32)                                                                    \
  _(vld4_u8)                                                                     \
  _(vld4_u16)                                                                    \
  _(vld4_u32)                                                                    \
  /*_(vld4_p8)                                                           */      \
  /*_(vld4_p16)                                                          */      \
  /*_(vld4_p64)                                                          */      \
  /*_(vld4q_s64)                                                              */ \
  /*_(vld4q_u64)                                                              */ \
  /*_(vld4q_p64)                                                              */ \
  /*_(vld4_f64)                                                               */ \
  /*_(vld4q_f64)                                                              */ \
  _(vld4_s64)                                                                    \
  _(vld4_u64)                                                                    \
  _(vld4q_s8)                                                                    \
  _(vld4q_s16)                                                                   \
  _(vld4q_s32)                                                                   \
  /*_(vld4q_f16)                                                         */      \
  _(vld4q_f32)                                                                   \
  _(vld4q_u8)                                                                    \
  _(vld4q_u16)                                                                   \
  _(vld4q_u32)                                                                   \
  /*_(vld4q_p8)                                                          */      \
  /*_(vld4q_p16)                                                         */      \
  _(vld4_lane_s8)                                                                \
  _(vld4_lane_s16)                                                               \
  _(vld4_lane_s32)                                                               \
  /*_(vld4_lane_f16)                                                     */      \
  _(vld4_lane_f32)                                                               \
  _(vld4_lane_u8)                                                                \
  _(vld4_lane_u16)                                                               \
  _(vld4_lane_u32)                                                               \
  /*_(vld4_lane_p8)                                                      */      \
  /*_(vld4q_lane_s8)                                                          */ \
  /*_(vld4q_lane_u8)                                                          */ \
  /*_(vld4q_lane_p8)                                                          */ \
  /*_(vld4_lane_s64)                                                          */ \
  /*_(vld4q_lane_s64)                                                         */ \
  /*_(vld4_lane_u64)                                                          */ \
  /*_(vld4q_lane_u64)                                                         */ \
  /*_(vld4_lane_p64)                                                          */ \
  /*_(vld4q_lane_p64)                                                         */ \
  /*_(vld4_lane_f64)                                                          */ \
  /*_(vld4q_lane_f64)                                                         */ \
  /*_(vld4_lane_p16)                                                     */      \
  _(vld4q_lane_s16)                                                              \
  _(vld4q_lane_s32)                                                              \
  /*_(vld4q_lane_f16)                                                    */      \
  _(vld4q_lane_f32)                                                              \
  _(vld4q_lane_u16)                                                              \
  _(vld4q_lane_u32)                                                              \
  /*_(vld4q_lane_p16)                                                    */      \
  _(vld4_dup_s8)                                                                 \
  /*_(vld4q_dup_s8)                                                           */ \
  _(vld4_dup_s16)                                                                \
  /*_(vld4q_dup_s16)                                                          */ \
  _(vld4_dup_s32)                                                                \
  /*_(vld4q_dup_s32)                                                          */ \
  /*_(vld4_dup_f16)                                                      */      \
  /*_(vld4q_dup_f16)                                                          */ \
  _(vld4_dup_f32)                                                                \
  /*_(vld4q_dup_f32)                                                          */ \
  _(vld4_dup_u8)                                                                 \
  /*_(vld4q_dup_u8)                                                           */ \
  _(vld4_dup_u16)                                                                \
  /*_(vld4q_dup_u16)                                                          */ \
  _(vld4_dup_u32)                                                                \
  /*_(vld4q_dup_u32)                                                          */ \
  /*_(vld4_dup_p8)                                                       */      \
  /*_(vld4q_dup_p8)                                                           */ \
  /*_(vld4_dup_p16)                                                      */      \
  /*_(vld4q_dup_p16)                                                          */ \
  /*_(vld4_dup_p64)                                                      */      \
  /*_(vld4q_dup_s64)                                                          */ \
  /*_(vld4q_dup_u64)                                                          */ \
  /*_(vld4q_dup_p64)                                                          */ \
  /*_(vld4_dup_f64)                                                           */ \
  /*_(vld4q_dup_f64)                                                          */ \
  _(vld4_dup_s64)                                                                \
  _(vld4_dup_u64)                                                                \
  _(vst4_s8)                                                                     \
  _(vst4_s16)                                                                    \
  _(vst4_s32)                                                                    \
  /*_(vst4_f16)                                                          */      \
  _(vst4_f32)                                                                    \
  _(vst4_u8)                                                                     \
  _(vst4_u16)                                                                    \
  _(vst4_u32)                                                                    \
  /*_(vst4_p8)                                                           */      \
  /*_(vst4_p16)                                                          */      \
  /*_(vst4_p64)                                                          */      \
  /*_(vst4q_s64)                                                              */ \
  /*_(vst4q_u64)                                                              */ \
  /*_(vst4q_p64)                                                              */ \
  /*_(vst4_f64)                                                               */ \
  /*_(vst4q_f64)                                                              */ \
  _(vst4_s64)                                                                    \
  _(vst4_u64)                                                                    \
  _(vst4q_s8)                                                                    \
  _(vst4q_s16)                                                                   \
  _(vst4q_s32)                                                                   \
  /*_(vst4q_f16)                                                         */      \
  _(vst4q_f32)                                                                   \
  _(vst4q_u8)                                                                    \
  _(vst4q_u16)                                                                   \
  _(vst4q_u32)                                                                   \
  /*_(vst4q_p8)                                                          */      \
  /*_(vst4q_p16)                                                         */      \
  _(vst4_lane_s8)                                                                \
  _(vst4_lane_s16)                                                               \
  _(vst4_lane_s32)                                                               \
  /*_(vst4_lane_f16)                                                     */      \
  _(vst4_lane_f32)                                                               \
  _(vst4_lane_u8)                                                                \
  _(vst4_lane_u16)                                                               \
  _(vst4_lane_u32)                                                               \
  /*_(vst4_lane_p8)                                                      */      \
  /*_(vst4_lane_p16)                                                     */      \
  _(vst4q_lane_s16)                                                              \
  _(vst4q_lane_s32)                                                              \
  /*_(vst4q_lane_f16)                                                    */      \
  _(vst4q_lane_f32)                                                              \
  _(vst4q_lane_u16)                                                              \
  _(vst4q_lane_u32)                                                              \
  /*_(vst4q_lane_p16)                                                    */      \
  /*_(vst4q_lane_s8)                                                          */ \
  /*_(vst4q_lane_u8)                                                          */ \
  /*_(vst4q_lane_p8)                                                          */ \
  /*_(vst4_lane_s64)                                                          */ \
  /*_(vst4q_lane_s64)                                                         */ \
  /*_(vst4_lane_u64)                                                          */ \
  /*_(vst4q_lane_u64)                                                         */ \
  /*_(vst4_lane_p64)                                                          */ \
  /*_(vst4q_lane_p64)                                                         */ \
  /*_(vst4_lane_f64)                                                          */ \
  /*_(vst4q_lane_f64)                                                         */ \
  /*_(vst1_s8_x2)                                                             */ \
  /*_(vst1q_s8_x2)                                                            */ \
  /*_(vst1_s16_x2)                                                            */ \
  /*_(vst1q_s16_x2)                                                           */ \
  /*_(vst1_s32_x2)                                                            */ \
  /*_(vst1q_s32_x2)                                                           */ \
  /*_(vst1_u8_x2)                                                             */ \
  /*_(vst1q_u8_x2)                                                            */ \
  /*_(vst1_u16_x2)                                                            */ \
  /*_(vst1q_u16_x2)                                                           */ \
  /*_(vst1_u32_x2)                                                            */ \
  /*_(vst1q_u32_x2)                                                           */ \
  /*_(vst1_f16_x2)                                                            */ \
  /*_(vst1q_f16_x2)                                                           */ \
  /*_(vst1_f32_x2)                                                            */ \
  /*_(vst1q_f32_x2)                                                           */ \
  /*_(vst1_p8_x2)                                                             */ \
  /*_(vst1q_p8_x2)                                                            */ \
  /*_(vst1_p16_x2)                                                            */ \
  /*_(vst1q_p16_x2)                                                           */ \
  /*_(vst1_s64_x2)                                                            */ \
  /*_(vst1_u64_x2)                                                            */ \
  /*_(vst1_p64_x2)                                                            */ \
  /*_(vst1q_s64_x2)                                                           */ \
  /*_(vst1q_u64_x2)                                                           */ \
  /*_(vst1q_p64_x2)                                                           */ \
  /*_(vst1_f64_x2)                                                            */ \
  /*_(vst1q_f64_x2)                                                           */ \
  /*_(vst1_s8_x3)                                                             */ \
  /*_(vst1q_s8_x3)                                                            */ \
  /*_(vst1_s16_x3)                                                            */ \
  /*_(vst1q_s16_x3)                                                           */ \
  /*_(vst1_s32_x3)                                                            */ \
  /*_(vst1q_s32_x3)                                                           */ \
  /*_(vst1_u8_x3)                                                             */ \
  /*_(vst1q_u8_x3)                                                            */ \
  /*_(vst1_u16_x3)                                                            */ \
  /*_(vst1q_u16_x3)                                                           */ \
  /*_(vst1_u32_x3)                                                            */ \
  /*_(vst1q_u32_x3)                                                           */ \
  /*_(vst1_f16_x3)                                                            */ \
  /*_(vst1q_f16_x3)                                                           */ \
  /*_(vst1_f32_x3)                                                            */ \
  /*_(vst1q_f32_x3)                                                           */ \
  /*_(vst1_p8_x3)                                                             */ \
  /*_(vst1q_p8_x3)                                                            */ \
  /*_(vst1_p16_x3)                                                            */ \
  /*_(vst1q_p16_x3)                                                           */ \
  /*_(vst1_s64_x3)                                                            */ \
  /*_(vst1_u64_x3)                                                            */ \
  /*_(vst1_p64_x3)                                                            */ \
  /*_(vst1q_s64_x3)                                                           */ \
  /*_(vst1q_u64_x3)                                                           */ \
  /*_(vst1q_p64_x3)                                                           */ \
  /*_(vst1_f64_x3)                                                            */ \
  /*_(vst1q_f64_x3)                                                           */ \
  /*_(vst1_s8_x4)                                                             */ \
  /*_(vst1q_s8_x4)                                                            */ \
  /*_(vst1_s16_x4)                                                            */ \
  /*_(vst1q_s16_x4)                                                           */ \
  /*_(vst1_s32_x4)                                                            */ \
  /*_(vst1q_s32_x4)                                                           */ \
  /*_(vst1_u8_x4)                                                             */ \
  /*_(vst1q_u8_x4)                                                            */ \
  /*_(vst1_u16_x4)                                                            */ \
  /*_(vst1q_u16_x4)                                                           */ \
  /*_(vst1_u32_x4)                                                            */ \
  /*_(vst1q_u32_x4)                                                           */ \
  /*_(vst1_f16_x4)                                                            */ \
  /*_(vst1q_f16_x4)                                                           */ \
  /*_(vst1_f32_x4)                                                            */ \
  /*_(vst1q_f32_x4)                                                           */ \
  /*_(vst1_p8_x4)                                                             */ \
  /*_(vst1q_p8_x4)                                                            */ \
  /*_(vst1_p16_x4)                                                            */ \
  /*_(vst1q_p16_x4)                                                           */ \
  /*_(vst1_s64_x4)                                                            */ \
  /*_(vst1_u64_x4)                                                            */ \
  /*_(vst1_p64_x4)                                                            */ \
  /*_(vst1q_s64_x4)                                                           */ \
  /*_(vst1q_u64_x4)                                                           */ \
  /*_(vst1q_p64_x4)                                                           */ \
  /*_(vst1_f64_x4)                                                            */ \
  /*_(vst1q_f64_x4)                                                           */ \
  /*_(vld1_s8_x2)                                                             */ \
  /*_(vld1q_s8_x2)                                                            */ \
  /*_(vld1_s16_x2)                                                            */ \
  /*_(vld1q_s16_x2)                                                           */ \
  /*_(vld1_s32_x2)                                                            */ \
  /*_(vld1q_s32_x2)                                                           */ \
  /*_(vld1_u8_x2)                                                             */ \
  /*_(vld1q_u8_x2)                                                            */ \
  /*_(vld1_u16_x2)                                                            */ \
  /*_(vld1q_u16_x2)                                                           */ \
  /*_(vld1_u32_x2)                                                            */ \
  /*_(vld1q_u32_x2)                                                           */ \
  /*_(vld1_f16_x2)                                                            */ \
  /*_(vld1q_f16_x2)                                                           */ \
  /*_(vld1_f32_x2)                                                            */ \
  /*_(vld1q_f32_x2)                                                           */ \
  /*_(vld1_p8_x2)                                                             */ \
  /*_(vld1q_p8_x2)                                                            */ \
  /*_(vld1_p16_x2)                                                            */ \
  /*_(vld1q_p16_x2)                                                           */ \
  /*_(vld1_s64_x2)                                                            */ \
  /*_(vld1_u64_x2)                                                            */ \
  /*_(vld1_p64_x2)                                                            */ \
  /*_(vld1q_s64_x2)                                                           */ \
  /*_(vld1q_u64_x2)                                                           */ \
  /*_(vld1q_p64_x2)                                                           */ \
  /*_(vld1_f64_x2)                                                            */ \
  /*_(vld1q_f64_x2)                                                           */ \
  /*_(vld1_s8_x3)                                                             */ \
  /*_(vld1q_s8_x3)                                                            */ \
  /*_(vld1_s16_x3)                                                            */ \
  /*_(vld1q_s16_x3)                                                           */ \
  /*_(vld1_s32_x3)                                                            */ \
  /*_(vld1q_s32_x3)                                                           */ \
  /*_(vld1_u8_x3)                                                             */ \
  /*_(vld1q_u8_x3)                                                            */ \
  /*_(vld1_u16_x3)                                                            */ \
  /*_(vld1q_u16_x3)                                                           */ \
  /*_(vld1_u32_x3)                                                            */ \
  /*_(vld1q_u32_x3)                                                           */ \
  /*_(vld1_f16_x3)                                                            */ \
  /*_(vld1q_f16_x3)                                                           */ \
  /*_(vld1_f32_x3)                                                            */ \
  /*_(vld1q_f32_x3)                                                           */ \
  /*_(vld1_p8_x3)                                                             */ \
  /*_(vld1q_p8_x3)                                                            */ \
  /*_(vld1_p16_x3)                                                            */ \
  /*_(vld1q_p16_x3)                                                           */ \
  /*_(vld1_s64_x3)                                                            */ \
  /*_(vld1_u64_x3)                                                            */ \
  /*_(vld1_p64_x3)                                                            */ \
  /*_(vld1q_s64_x3)                                                           */ \
  /*_(vld1q_u64_x3)                                                           */ \
  /*_(vld1q_p64_x3)                                                           */ \
  /*_(vld1_f64_x3)                                                            */ \
  /*_(vld1q_f64_x3)                                                           */ \
  /*_(vld1_s8_x4)                                                             */ \
  /*_(vld1q_s8_x4)                                                            */ \
  /*_(vld1_s16_x4)                                                            */ \
  /*_(vld1q_s16_x4)                                                           */ \
  /*_(vld1_s32_x4)                                                            */ \
  /*_(vld1q_s32_x4)                                                           */ \
  /*_(vld1_u8_x4)                                                             */ \
  /*_(vld1q_u8_x4)                                                            */ \
  /*_(vld1_u16_x4)                                                            */ \
  /*_(vld1q_u16_x4)                                                           */ \
  /*_(vld1_u32_x4)                                                            */ \
  /*_(vld1q_u32_x4)                                                           */ \
  /*_(vld1_f16_x4)                                                            */ \
  /*_(vld1q_f16_x4)                                                           */ \
  /*_(vld1_f32_x4)                                                            */ \
  /*_(vld1q_f32_x4)                                                           */ \
  /*_(vld1_p8_x4)                                                             */ \
  /*_(vld1q_p8_x4)                                                            */ \
  /*_(vld1_p16_x4)                                                            */ \
  /*_(vld1q_p16_x4)                                                           */ \
  /*_(vld1_s64_x4)                                                            */ \
  /*_(vld1_u64_x4)                                                            */ \
  /*_(vld1_p64_x4)                                                            */ \
  /*_(vld1q_s64_x4)                                                           */ \
  /*_(vld1q_u64_x4)                                                           */ \
  /*_(vld1q_p64_x4)                                                           */ \
  /*_(vld1_f64_x4)                                                            */ \
  /*_(vld1q_f64_x4)                                                           */ \
  _(vand_s8)                                                                     \
  _(vand_s16)                                                                    \
  _(vand_s32)                                                                    \
  _(vand_u8)                                                                     \
  _(vand_u16)                                                                    \
  _(vand_u32)                                                                    \
  _(vand_s64)                                                                    \
  _(vand_u64)                                                                    \
  _(vandq_s8)                                                                    \
  _(vandq_s16)                                                                   \
  _(vandq_s32)                                                                   \
  _(vandq_s64)                                                                   \
  _(vandq_u8)                                                                    \
  _(vandq_u16)                                                                   \
  _(vandq_u32)                                                                   \
  _(vandq_u64)                                                                   \
  _(vorr_s8)                                                                     \
  _(vorr_s16)                                                                    \
  _(vorr_s32)                                                                    \
  _(vorr_u8)                                                                     \
  _(vorr_u16)                                                                    \
  _(vorr_u32)                                                                    \
  _(vorr_s64)                                                                    \
  _(vorr_u64)                                                                    \
  _(vorrq_s8)                                                                    \
  _(vorrq_s16)                                                                   \
  _(vorrq_s32)                                                                   \
  _(vorrq_s64)                                                                   \
  _(vorrq_u8)                                                                    \
  _(vorrq_u16)                                                                   \
  _(vorrq_u32)                                                                   \
  _(vorrq_u64)                                                                   \
  _(veor_s8)                                                                     \
  _(veor_s16)                                                                    \
  _(veor_s32)                                                                    \
  _(veor_u8)                                                                     \
  _(veor_u16)                                                                    \
  _(veor_u32)                                                                    \
  _(veor_s64)                                                                    \
  _(veor_u64)                                                                    \
  _(veorq_s8)                                                                    \
  _(veorq_s16)                                                                   \
  _(veorq_s32)                                                                   \
  _(veorq_s64)                                                                   \
  _(veorq_u8)                                                                    \
  _(veorq_u16)                                                                   \
  _(veorq_u32)                                                                   \
  _(veorq_u64)                                                                   \
  _(vbic_s8)                                                                     \
  _(vbic_s16)                                                                    \
  _(vbic_s32)                                                                    \
  _(vbic_u8)                                                                     \
  _(vbic_u16)                                                                    \
  _(vbic_u32)                                                                    \
  _(vbic_s64)                                                                    \
  _(vbic_u64)                                                                    \
  _(vbicq_s8)                                                                    \
  _(vbicq_s16)                                                                   \
  _(vbicq_s32)                                                                   \
  _(vbicq_s64)                                                                   \
  _(vbicq_u8)                                                                    \
  _(vbicq_u16)                                                                   \
  _(vbicq_u32)                                                                   \
  _(vbicq_u64)                                                                   \
  _(vorn_s8)                                                                     \
  _(vorn_s16)                                                                    \
  _(vorn_s32)                                                                    \
  _(vorn_u8)                                                                     \
  _(vorn_u16)                                                                    \
  _(vorn_u32)                                                                    \
  _(vorn_s64)                                                                    \
  _(vorn_u64)                                                                    \
  _(vornq_s8)                                                                    \
  _(vornq_s16)                                                                   \
  _(vornq_s32)                                                                   \
  _(vornq_s64)                                                                   \
  _(vornq_u8)                                                                    \
  _(vornq_u16)                                                                   \
  _(vornq_u32)                                                                   \
  _(vornq_u64)                                                                   \
  /*_(vreinterpret_p8_p16)                                               */      \
  /*_(vreinterpret_p8_f16)                                               */      \
  /*_(vreinterpret_p8_f32)                                               */      \
  /*_(vreinterpret_p8_p64)                                               */      \
  /*_(vreinterpret_p8_s64)                                               */      \
  /*_(vreinterpret_p8_u64)                                               */      \
  /*_(vreinterpret_p8_s8)                                                */      \
  /*_(vreinterpret_p8_s16)                                               */      \
  /*_(vreinterpret_p8_s32)                                               */      \
  /*_(vreinterpret_p8_u8)                                                */      \
  /*_(vreinterpret_p8_u16)                                               */      \
  /*_(vreinterpret_p8_u32)                                               */      \
  /*_(vreinterpret_p16_p8)                                               */      \
  /*_(vreinterpret_p16_f16)                                              */      \
  /*_(vreinterpret_p16_f32)                                              */      \
  /*_(vreinterpret_p16_p64)                                              */      \
  /*_(vreinterpret_p16_s64)                                              */      \
  /*_(vreinterpret_p16_u64)                                              */      \
  /*_(vreinterpret_p16_s8)                                               */      \
  /*_(vreinterpret_p16_s16)                                              */      \
  /*_(vreinterpret_p16_s32)                                              */      \
  /*_(vreinterpret_p16_u8)                                               */      \
  /*_(vreinterpret_p16_u16)                                              */      \
  /*_(vreinterpret_p16_u32)                                              */      \
  /*_(vreinterpret_f16_bf16)                                             */      \
  /*_(vreinterpret_f16_p8)                                               */      \
  /*_(vreinterpret_f16_p16)                                              */      \
  /*_(vreinterpret_f16_f32)                                              */      \
  /*_(vreinterpret_f16_p64)                                              */      \
  /*_(vreinterpret_f16_s64)                                              */      \
  /*_(vreinterpret_f16_u64)                                              */      \
  /*_(vreinterpret_f16_s8)                                               */      \
  /*_(vreinterpret_f16_s16)                                              */      \
  /*_(vreinterpret_f16_s32)                                              */      \
  /*_(vreinterpret_f16_u8)                                               */      \
  /*_(vreinterpret_f16_u16)                                              */      \
  /*_(vreinterpret_f16_u32)                                              */      \
  /*_(vreinterpret_f32_p8)                                               */      \
  /*_(vreinterpret_f32_p16)                                              */      \
  /*_(vreinterpret_f32_f16)                                              */      \
  /*_(vreinterpret_f32_p64)                                              */      \
  _(vreinterpret_f32_s64)                                                        \
  _(vreinterpret_f32_u64)                                                        \
  _(vreinterpret_f32_s8)                                                         \
  _(vreinterpret_f32_s16)                                                        \
  _(vreinterpret_f32_s32)                                                        \
  _(vreinterpret_f32_u8)                                                         \
  _(vreinterpret_f32_u16)                                                        \
  _(vreinterpret_f32_u32)                                                        \
  /*_(vreinterpret_p64_p8)                                               */      \
  /*_(vreinterpret_p64_p16)                                              */      \
  /*_(vreinterpret_p64_f16)                                              */      \
  /*_(vreinterpret_p64_f32)                                              */      \
  /*_(vreinterpret_p64_f64)                                                   */ \
  /*_(vreinterpret_p64_s64)                                              */      \
  /*_(vreinterpret_p64_u64)                                              */      \
  /*_(vreinterpret_p64_s8)                                               */      \
  /*_(vreinterpret_p64_s16)                                              */      \
  /*_(vreinterpret_p64_s32)                                              */      \
  /*_(vreinterpret_p64_u8)                                               */      \
  /*_(vreinterpret_p64_u16)                                              */      \
  /*_(vreinterpret_p64_u32)                                              */      \
  /*_(vreinterpret_s64_p8)                                               */      \
  /*_(vreinterpret_f64_p8)                                                    */ \
  /*_(vreinterpret_s64_p16)                                              */      \
  /*_(vreinterpret_f64_p16)                                                   */ \
  /*_(vreinterpret_s64_f16)                                              */      \
  /*_(vreinterpret_f64_f16)                                                   */ \
  _(vreinterpret_s64_f32)                                                        \
  /*_(vreinterpret_f64_f32)                                                   */ \
  /*_(vreinterpret_s64_p64)                                              */      \
  /*_(vreinterpret_f64_p64)                                                   */ \
  _(vreinterpret_s64_u64)                                                        \
  /*_(vreinterpret_f64_u64)                                                   */ \
  _(vreinterpret_s64_s8)                                                         \
  /*_(vreinterpret_f64_s8)                                                    */ \
  _(vreinterpret_s64_s16)                                                        \
  /*_(vreinterpret_f64_s16)                                                   */ \
  _(vreinterpret_s64_s32)                                                        \
  /*_(vreinterpret_f64_s32)                                                   */ \
  _(vreinterpret_s64_u8)                                                         \
  /*_(vreinterpret_f64_u8)                                                    */ \
  _(vreinterpret_s64_u16)                                                        \
  /*_(vreinterpret_f64_u16)                                                   */ \
  _(vreinterpret_s64_u32)                                                        \
  /*_(vreinterpret_f64_u32)                                                   */ \
  /*_(vreinterpret_u64_p8)                                               */      \
  /*_(vreinterpret_u64_p16)                                              */      \
  /*_(vreinterpret_u64_f16)                                              */      \
  _(vreinterpret_u64_f32)                                                        \
  /*_(vreinterpret_u64_p64)                                              */      \
  _(vreinterpret_u64_s64)                                                        \
  /*_(vreinterpret_f64_s64)                                                   */ \
  _(vreinterpret_u64_s8)                                                         \
  _(vreinterpret_u64_s16)                                                        \
  _(vreinterpret_u64_s32)                                                        \
  _(vreinterpret_u64_u8)                                                         \
  _(vreinterpret_u64_u16)                                                        \
  _(vreinterpret_u64_u32)                                                        \
  /*_(vreinterpret_s8_p8)                                                */      \
  /*_(vreinterpret_s8_p16)                                               */      \
  /*_(vreinterpret_s8_f16)                                               */      \
  _(vreinterpret_s8_f32)                                                         \
  /*_(vreinterpret_s8_p64)                                               */      \
  _(vreinterpret_s8_s64)                                                         \
  _(vreinterpret_s8_u64)                                                         \
  _(vreinterpret_s8_s16)                                                         \
  _(vreinterpret_s8_s32)                                                         \
  _(vreinterpret_s8_u8)                                                          \
  _(vreinterpret_s8_u16)                                                         \
  _(vreinterpret_s8_u32)                                                         \
  /*_(vreinterpret_s16_p8)                                               */      \
  /*_(vreinterpret_s16_p16)                                              */      \
  /*_(vreinterpret_s16_f16)                                              */      \
  _(vreinterpret_s16_f32)                                                        \
  /*_(vreinterpret_s16_p64)                                              */      \
  _(vreinterpret_s16_s64)                                                        \
  _(vreinterpret_s16_u64)                                                        \
  _(vreinterpret_s16_s8)                                                         \
  _(vreinterpret_s16_s32)                                                        \
  _(vreinterpret_s16_u8)                                                         \
  _(vreinterpret_s16_u16)                                                        \
  _(vreinterpret_s16_u32)                                                        \
  /*_(vreinterpret_s32_p8)                                               */      \
  /*_(vreinterpret_s32_p16)                                              */      \
  /*_(vreinterpret_s32_f16)                                              */      \
  _(vreinterpret_s32_f32)                                                        \
  /*_(vreinterpret_s32_p64)                                              */      \
  _(vreinterpret_s32_s64)                                                        \
  _(vreinterpret_s32_u64)                                                        \
  _(vreinterpret_s32_s8)                                                         \
  _(vreinterpret_s32_s16)                                                        \
  _(vreinterpret_s32_u8)                                                         \
  _(vreinterpret_s32_u16)                                                        \
  _(vreinterpret_s32_u32)                                                        \
  /*_(vreinterpret_u8_p8)                                                */      \
  /*_(vreinterpret_u8_p16)                                               */      \
  /*_(vreinterpret_u8_f16)                                               */      \
  _(vreinterpret_u8_f32)                                                         \
  /*_(vreinterpret_u8_p64)                                               */      \
  _(vreinterpret_u8_s64)                                                         \
  _(vreinterpret_u8_u64)                                                         \
  _(vreinterpret_u8_s8)                                                          \
  _(vreinterpret_u8_s16)                                                         \
  _(vreinterpret_u8_s32)                                                         \
  _(vreinterpret_u8_u16)                                                         \
  _(vreinterpret_u8_u32)                                                         \
  /*_(vreinterpret_u16_p8)                                               */      \
  /*_(vreinterpret_u16_p16)                                              */      \
  /*_(vreinterpret_u16_f16)                                              */      \
  _(vreinterpret_u16_f32)                                                        \
  /*_(vreinterpret_u16_p64)                                              */      \
  _(vreinterpret_u16_s64)                                                        \
  _(vreinterpret_u16_u64)                                                        \
  _(vreinterpret_u16_s8)                                                         \
  _(vreinterpret_u16_s16)                                                        \
  _(vreinterpret_u16_s32)                                                        \
  _(vreinterpret_u16_u8)                                                         \
  _(vreinterpret_u16_u32)                                                        \
  /*_(vreinterpret_u32_p8)                                               */      \
  /*_(vreinterpret_u32_p16)                                              */      \
  /*_(vreinterpret_u32_f16)                                              */      \
  _(vreinterpret_u32_f32)                                                        \
  /*_(vreinterpret_u32_p64)                                              */      \
  _(vreinterpret_u32_s64)                                                        \
  _(vreinterpret_u32_u64)                                                        \
  _(vreinterpret_u32_s8)                                                         \
  _(vreinterpret_u32_s16)                                                        \
  _(vreinterpret_u32_s32)                                                        \
  _(vreinterpret_u32_u8)                                                         \
  _(vreinterpret_u32_u16)                                                        \
  /*_(vreinterpretq_p8_p16)                                              */      \
  /*_(vreinterpretq_p8_f16)                                              */      \
  /*_(vreinterpretq_p8_f32)                                              */      \
  /*_(vreinterpretq_p8_p64)                                              */      \
  /*_(vreinterpretq_p8_p128)                                             */      \
  /*_(vreinterpretq_p8_s64)                                              */      \
  /*_(vreinterpretq_p8_u64)                                              */      \
  /*_(vreinterpretq_p8_s8)                                               */      \
  /*_(vreinterpretq_p8_s16)                                              */      \
  /*_(vreinterpretq_p8_s32)                                              */      \
  /*_(vreinterpretq_p8_u8)                                               */      \
  /*_(vreinterpretq_p8_u16)                                              */      \
  /*_(vreinterpretq_p8_u32)                                              */      \
  /*_(vreinterpretq_p16_p8)                                              */      \
  /*_(vreinterpretq_p16_f16)                                             */      \
  /*_(vreinterpretq_p16_f32)                                             */      \
  /*_(vreinterpretq_p16_p64)                                             */      \
  /*_(vreinterpretq_p16_p128)                                            */      \
  /*_(vreinterpretq_p16_s64)                                             */      \
  /*_(vreinterpretq_p16_u64)                                             */      \
  /*_(vreinterpretq_p16_s8)                                              */      \
  /*_(vreinterpretq_p16_s16)                                             */      \
  /*_(vreinterpretq_p16_s32)                                             */      \
  /*_(vreinterpretq_p16_u8)                                              */      \
  /*_(vreinterpretq_p16_u16)                                             */      \
  /*_(vreinterpretq_p16_u32)                                             */      \
  /*_(vreinterpretq_f16_p8)                                              */      \
  /*_(vreinterpretq_f16_p16)                                             */      \
  /*_(vreinterpretq_f16_bf16)                                            */      \
  /*_(vreinterpretq_f16_f32)                                             */      \
  /*_(vreinterpretq_f16_p64)                                             */      \
  /*_(vreinterpretq_f16_p128)                                            */      \
  /*_(vreinterpretq_f16_s64)                                             */      \
  /*_(vreinterpretq_f16_u64)                                             */      \
  /*_(vreinterpretq_f16_s8)                                              */      \
  /*_(vreinterpretq_f16_s16)                                             */      \
  /*_(vreinterpretq_f16_s32)                                             */      \
  /*_(vreinterpretq_f16_u8)                                              */      \
  /*_(vreinterpretq_f16_u16)                                             */      \
  /*_(vreinterpretq_f16_u32)                                             */      \
  /*_(vreinterpretq_f32_p8)                                              */      \
  /*_(vreinterpretq_f32_p16)                                             */      \
  /*_(vreinterpretq_f32_f16)                                             */      \
  /*_(vreinterpretq_f32_p64)                                             */      \
  /*_(vreinterpretq_f32_p128)                                            */      \
  _(vreinterpretq_f32_s64)                                                       \
  _(vreinterpretq_f32_u64)                                                       \
  _(vreinterpretq_f32_s8)                                                        \
  _(vreinterpretq_f32_s16)                                                       \
  _(vreinterpretq_f32_s32)                                                       \
  _(vreinterpretq_f32_u8)                                                        \
  _(vreinterpretq_f32_u16)                                                       \
  _(vreinterpretq_f32_u32)                                                       \
  /*_(vreinterpretq_p64_p8)                                              */      \
  /*_(vreinterpretq_p64_p16)                                             */      \
  /*_(vreinterpretq_p64_f16)                                             */      \
  /*_(vreinterpretq_p64_f32)                                             */      \
  /*_(vreinterpretq_p64_p128)                                            */      \
  /*_(vreinterpretq_p64_s64)                                             */      \
  /*_(vreinterpretq_p64_u64)                                             */      \
  /*_(vreinterpretq_p64_s8)                                              */      \
  /*_(vreinterpretq_p64_s16)                                             */      \
  /*_(vreinterpretq_p64_s32)                                             */      \
  /*_(vreinterpretq_p64_u8)                                              */      \
  /*_(vreinterpretq_p64_u16)                                             */      \
  /*_(vreinterpretq_p64_u32)                                             */      \
  /*_(vreinterpretq_p128_p8)                                             */      \
  /*_(vreinterpretq_p128_p16)                                            */      \
  /*_(vreinterpretq_p128_f16)                                            */      \
  /*_(vreinterpret_s8_f64)                                                    */ \
  /*_(vreinterpret_s16_f64)                                                   */ \
  /*_(vreinterpret_s32_f64)                                                   */ \
  /*_(vreinterpret_u8_f64)                                                    */ \
  /*_(vreinterpret_u16_f64)                                                   */ \
  /*_(vreinterpret_u32_f64)                                                   */ \
  /*_(vreinterpret_p8_f64)                                                    */ \
  /*_(vreinterpret_p16_f64)                                                   */ \
  /*_(vreinterpret_u64_f64)                                                   */ \
  /*_(vreinterpret_s64_f64)                                                   */ \
  /*_(vreinterpret_f16_f64)                                                   */ \
  /*_(vreinterpret_f32_f64)                                                   */ \
  /*_(vreinterpretq_s8_f64)                                                   */ \
  /*_(vreinterpretq_s16_f64)                                                  */ \
  /*_(vreinterpretq_s32_f64)                                                  */ \
  /*_(vreinterpretq_u8_f64)                                                   */ \
  /*_(vreinterpretq_u16_f64)                                                  */ \
  /*_(vreinterpretq_u32_f64)                                                  */ \
  /*_(vreinterpretq_p8_f64)                                                   */ \
  /*_(vreinterpretq_p16_f64)                                                  */ \
  /*_(vreinterpretq_u64_f64)                                                  */ \
  /*_(vreinterpretq_s64_f64)                                                  */ \
  /*_(vreinterpretq_f16_f64)                                                  */ \
  /*_(vreinterpretq_f32_f64)                                                  */ \
  /*_(vreinterpretq_p128_f32)                                            */      \
  /*_(vreinterpretq_p64_f64)                                                  */ \
  /*_(vreinterpretq_p128_f64)                                                 */ \
  /*_(vreinterpretq_p128_p64)                                            */      \
  /*_(vreinterpretq_p128_s64)                                            */      \
  /*_(vreinterpretq_p128_u64)                                            */      \
  /*_(vreinterpretq_p128_s8)                                             */      \
  /*_(vreinterpretq_p128_s16)                                            */      \
  /*_(vreinterpretq_p128_s32)                                            */      \
  /*_(vreinterpretq_p128_u8)                                             */      \
  /*_(vreinterpretq_p128_u16)                                            */      \
  /*_(vreinterpretq_p128_u32)                                            */      \
  /*_(vreinterpretq_s64_p8)                                              */      \
  /*_(vreinterpretq_f64_p8)                                                   */ \
  /*_(vreinterpretq_s64_p16)                                             */      \
  /*_(vreinterpretq_f64_p16)                                                  */ \
  /*_(vreinterpretq_s64_f16)                                             */      \
  /*_(vreinterpretq_f64_f16)                                                  */ \
  _(vreinterpretq_s64_f32)                                                       \
  /*_(vreinterpretq_f64_f32)                                                  */ \
  /*_(vreinterpretq_s64_p64)                                             */      \
  /*_(vreinterpretq_f64_p64)                                                  */ \
  /*_(vreinterpretq_s64_p128)                                            */      \
  /*_(vreinterpretq_f64_p128)                                                 */ \
  _(vreinterpretq_s64_u64)                                                       \
  /*_(vreinterpretq_f64_u64)                                                  */ \
  /*_(vreinterpretq_f64_s64)                                                  */ \
  _(vreinterpretq_s64_s8)                                                        \
  /*_(vreinterpretq_f64_s8)                                                   */ \
  _(vreinterpretq_s64_s16)                                                       \
  /*_(vreinterpretq_f64_s16)                                                  */ \
  _(vreinterpretq_s64_s32)                                                       \
  /*_(vreinterpretq_f64_s32)                                                  */ \
  _(vreinterpretq_s64_u8)                                                        \
  /*_(vreinterpretq_f64_u8)                                                   */ \
  _(vreinterpretq_s64_u16)                                                       \
  /*_(vreinterpretq_f64_u16)                                                  */ \
  _(vreinterpretq_s64_u32)                                                       \
  /*_(vreinterpretq_f64_u32)                                                  */ \
  /*_(vreinterpretq_u64_p8)                                              */      \
  /*_(vreinterpretq_u64_p16)                                             */      \
  /*_(vreinterpretq_u64_f16)                                             */      \
  _(vreinterpretq_u64_f32)                                                       \
  /*_(vreinterpretq_u64_p64)                                             */      \
  /*_(vreinterpretq_u64_p128)                                            */      \
  _(vreinterpretq_u64_s64)                                                       \
  _(vreinterpretq_u64_s8)                                                        \
  _(vreinterpretq_u64_s16)                                                       \
  _(vreinterpretq_u64_s32)                                                       \
  _(vreinterpretq_u64_u8)                                                        \
  _(vreinterpretq_u64_u16)                                                       \
  _(vreinterpretq_u64_u32)                                                       \
  /*_(vreinterpretq_s8_p8)                                               */      \
  /*_(vreinterpretq_s8_p16)                                              */      \
  /*_(vreinterpretq_s8_f16)                                              */      \
  _(vreinterpretq_s8_f32)                                                        \
  /*_(vreinterpretq_s8_p64)                                              */      \
  /*_(vreinterpretq_s8_p128)                                             */      \
  _(vreinterpretq_s8_s64)                                                        \
  _(vreinterpretq_s8_u64)                                                        \
  _(vreinterpretq_s8_s16)                                                        \
  _(vreinterpretq_s8_s32)                                                        \
  _(vreinterpretq_s8_u8)                                                         \
  _(vreinterpretq_s8_u16)                                                        \
  _(vreinterpretq_s8_u32)                                                        \
  /*_(vreinterpretq_s16_p8)                                              */      \
  /*_(vreinterpretq_s16_p16)                                             */      \
  /*_(vreinterpretq_s16_f16)                                             */      \
  _(vreinterpretq_s16_f32)                                                       \
  /*_(vreinterpretq_s16_p64)                                             */      \
  /*_(vreinterpretq_s16_p128)                                            */      \
  _(vreinterpretq_s16_s64)                                                       \
  _(vreinterpretq_s16_u64)                                                       \
  _(vreinterpretq_s16_s8)                                                        \
  _(vreinterpretq_s16_s32)                                                       \
  _(vreinterpretq_s16_u8)                                                        \
  _(vreinterpretq_s16_u16)                                                       \
  _(vreinterpretq_s16_u32)                                                       \
  /*_(vreinterpretq_s32_p8)                                              */      \
  /*_(vreinterpretq_s32_p16)                                             */      \
  /*_(vreinterpretq_s32_f16)                                             */      \
  _(vreinterpretq_s32_f32)                                                       \
  /*_(vreinterpretq_s32_p64)                                             */      \
  /*_(vreinterpretq_s32_p128)                                            */      \
  _(vreinterpretq_s32_s64)                                                       \
  _(vreinterpretq_s32_u64)                                                       \
  _(vreinterpretq_s32_s8)                                                        \
  _(vreinterpretq_s32_s16)                                                       \
  _(vreinterpretq_s32_u8)                                                        \
  _(vreinterpretq_s32_u16)                                                       \
  _(vreinterpretq_s32_u32)                                                       \
  /*_(vreinterpretq_u8_p8)                                               */      \
  /*_(vreinterpretq_u8_p16)                                              */      \
  /*_(vreinterpretq_u8_f16)                                              */      \
  _(vreinterpretq_u8_f32)                                                        \
  /*_(vreinterpretq_u8_p64)                                              */      \
  /*_(vreinterpretq_u8_p128)                                             */      \
  _(vreinterpretq_u8_s64)                                                        \
  _(vreinterpretq_u8_u64)                                                        \
  _(vreinterpretq_u8_s8)                                                         \
  _(vreinterpretq_u8_s16)                                                        \
  _(vreinterpretq_u8_s32)                                                        \
  _(vreinterpretq_u8_u16)                                                        \
  _(vreinterpretq_u8_u32)                                                        \
  /*_(vreinterpretq_u16_p8)                                              */      \
  /*_(vreinterpretq_u16_p16)                                             */      \
  /*_(vreinterpretq_u16_f16)                                             */      \
  _(vreinterpretq_u16_f32)                                                       \
  /*_(vreinterpretq_u16_p64)                                             */      \
  /*_(vreinterpretq_u16_p128)                                            */      \
  _(vreinterpretq_u16_s64)                                                       \
  _(vreinterpretq_u16_u64)                                                       \
  _(vreinterpretq_u16_s8)                                                        \
  _(vreinterpretq_u16_s16)                                                       \
  _(vreinterpretq_u16_s32)                                                       \
  _(vreinterpretq_u16_u8)                                                        \
  _(vreinterpretq_u16_u32)                                                       \
  /*_(vreinterpretq_u32_p8)                                              */      \
  /*_(vreinterpretq_u32_p16)                                             */      \
  /*_(vreinterpretq_u32_f16)                                             */      \
  _(vreinterpretq_u32_f32)                                                       \
  /*_(vreinterpretq_u32_p64)                                             */      \
  /*_(vreinterpretq_u32_p128)                                            */      \
  _(vreinterpretq_u32_s64)                                                       \
  _(vreinterpretq_u32_u64)                                                       \
  _(vreinterpretq_u32_s8)                                                        \
  _(vreinterpretq_u32_s16)                                                       \
  _(vreinterpretq_u32_s32)                                                       \
  _(vreinterpretq_u32_u8)                                                        \
  _(vreinterpretq_u32_u16)                                                       \
  /*_(vldrq_p128)                                                        */      \
  /*_(vstrq_p128)                                                        */      \
  /*_(vceq_p64)                                                          */      \
  /*_(vceqz_p64)                                                         */      \
  /*_(vceqq_p64)                                                         */      \
  /*_(vceq_f64)                                                               */ \
  /*_(vceqq_f64)                                                              */ \
  /*_(vceqd_s64)                                                              */ \
  /*_(vceqd_u64)                                                              */ \
  /*_(vceqs_f32)                                                              */ \
  /*_(vceqd_f64)                                                              */ \
  /*_(vceqz_s8)                                                               */ \
  /*_(vceqzq_s8)                                                              */ \
  /*_(vceqz_s16)                                                              */ \
  /*_(vceqzq_s16)                                                             */ \
  /*_(vceqz_s32)                                                              */ \
  /*_(vceqzq_s32)                                                             */ \
  /*_(vceqz_u8)                                                               */ \
  /*_(vceqzq_u8)                                                              */ \
  /*_(vceqz_u16)                                                              */ \
  /*_(vceqzq_u16)                                                             */ \
  /*_(vceqz_u32)                                                              */ \
  /*_(vceqzq_u32)                                                             */ \
  /*_(vceqz_f32)                                                              */ \
  /*_(vceqzq_f32)                                                             */ \
  /*_(vceqz_p8)                                                               */ \
  /*_(vceqzq_p8)                                                              */ \
  /*_(vceqz_s64)                                                              */ \
  /*_(vceqzq_s64)                                                             */ \
  /*_(vceqz_u64)                                                              */ \
  /*_(vceqzq_u64)                                                             */ \
  /*_(vceqzq_p64)                                                        */      \
  /*_(vceqz_f64)                                                              */ \
  /*_(vceqzq_f64)                                                             */ \
  /*_(vceqzd_s64)                                                             */ \
  /*_(vceqzd_u64)                                                             */ \
  /*_(vceqzs_f32)                                                             */ \
  /*_(vceqzd_f64)                                                             */ \
  /*_(vtst_p64)                                                          */      \
  /*_(vtstq_p64)                                                              */ \
  /*_(vtstd_s64)                                                              */ \
  /*_(vtstd_u64)                                                              */ \
  _(vaeseq_u8)                                                                   \
  _(vaesdq_u8)                                                                   \
  _(vaesmcq_u8)                                                                  \
  _(vaesimcq_u8)                                                                 \
  _(vsha1h_u32)                                                                  \
  _(vsha1cq_u32)                                                                 \
  _(vsha1pq_u32)                                                                 \
  _(vsha1mq_u32)                                                                 \
  _(vsha1su0q_u32)                                                               \
  _(vsha1su1q_u32)                                                               \
  _(vsha256hq_u32)                                                               \
  _(vsha256h2q_u32)                                                              \
  _(vsha256su0q_u32)                                                             \
  _(vsha256su1q_u32)                                                             \
  /*_(vmull_p64)                                                         */      \
  /*_(vmull_high_p64)                                                    */      \
  /*_(vadd_p8)                                                                */ \
  /*_(vadd_p16)                                                               */ \
  /*_(vadd_p64)                                                               */ \
  /*_(vaddq_p8)                                                               */ \
  /*_(vaddq_p16)                                                              */ \
  /*_(vaddq_p64)                                                              */ \
  /*_(vaddq_p128)                                                             */ \
  /*_(__crc32b)                                                               */ \
  /*_(__crc32h)                                                               */ \
  /*_(__crc32w)                                                               */ \
  /*_(__crc32d)                                                               */ \
  /*_(__crc32cb)                                                              */ \
  /*_(__crc32ch)                                                              */ \
  /*_(__crc32cw)                                                              */ \
  /*_(__crc32cd)                                                              */ \
  /* Intrinsics for FP16 instructions. */                                        \
  /*_(vabd_f16)                                                          */      \
  /*_(vabdq_f16)                                                         */      \
  /*_(vabs_f16)                                                          */      \
  /*_(vabsq_f16)                                                         */      \
  /*_(vadd_f16)                                                          */      \
  /*_(vaddq_f16)                                                         */      \
  /*_(vcage_f16)                                                         */      \
  /*_(vcageq_f16)                                                        */      \
  /*_(vcagt_f16)                                                         */      \
  /*_(vcagtq_f16)                                                        */      \
  /*_(vcale_f16)                                                         */      \
  /*_(vcaleq_f16)                                                        */      \
  /*_(vcalt_f16)                                                         */      \
  /*_(vcaltq_f16)                                                        */      \
  /*_(vceq_f16)                                                          */      \
  /*_(vceqq_f16)                                                         */      \
  /*_(vceqz_f16)                                                         */      \
  /*_(vceqzq_f16)                                                        */      \
  /*_(vcge_f16)                                                          */      \
  /*_(vcgeq_f16)                                                         */      \
  /*_(vcgez_f16)                                                         */      \
  /*_(vcgezq_f16)                                                        */      \
  /*_(vcgt_f16)                                                          */      \
  /*_(vcgtq_f16)                                                         */      \
  /*_(vcgtz_f16)                                                         */      \
  /*_(vcgtzq_f16)                                                        */      \
  /*_(vcle_f16)                                                          */      \
  /*_(vcleq_f16)                                                         */      \
  /*_(vclez_f16)                                                         */      \
  /*_(vclezq_f16)                                                        */      \
  /*_(vclt_f16)                                                          */      \
  /*_(vcltq_f16)                                                         */      \
  /*_(vcltz_f16)                                                         */      \
  /*_(vcltzq_f16)                                                        */      \
  /*_(vcvt_f16_s16)                                                      */      \
  /*_(vcvt_f16_u16)                                                      */      \
  /*_(vcvt_s16_f16)                                                      */      \
  /*_(vcvt_u16_f16)                                                      */      \
  /*_(vcvtq_f16_s16)                                                     */      \
  /*_(vcvtq_f16_u16)                                                     */      \
  /*_(vcvtq_s16_f16)                                                     */      \
  /*_(vcvtq_u16_f16)                                                     */      \
  /*_(vcvta_s16_f16)                                                     */      \
  /*_(vcvta_u16_f16)                                                     */      \
  /*_(vcvtaq_s16_f16)                                                    */      \
  /*_(vcvtaq_u16_f16)                                                    */      \
  /*_(vcvtm_s16_f16)                                                     */      \
  /*_(vcvtm_u16_f16)                                                     */      \
  /*_(vcvtmq_s16_f16)                                                    */      \
  /*_(vcvtmq_u16_f16)                                                    */      \
  /*_(vcvtn_s16_f16)                                                     */      \
  /*_(vcvtn_u16_f16)                                                     */      \
  /*_(vcvtnq_s16_f16)                                                    */      \
  /*_(vcvtnq_u16_f16)                                                    */      \
  /*_(vcvtp_s16_f16)                                                     */      \
  /*_(vcvtp_u16_f16)                                                     */      \
  /*_(vcvtpq_s16_f16)                                                    */      \
  /*_(vcvtpq_u16_f16)                                                    */      \
  /*_(vcvt_n_f16_s16)                                                    */      \
  /*_(vcvt_n_f16_u16)                                                    */      \
  /*_(vcvtq_n_f16_s16)                                                   */      \
  /*_(vcvtq_n_f16_u16)                                                   */      \
  /*_(vcvt_n_s16_f16)                                                    */      \
  /*_(vcvt_n_u16_f16)                                                    */      \
  /*_(vcvtq_n_s16_f16)                                                   */      \
  /*_(vcvtq_n_u16_f16)                                                   */      \
  /*_(vdiv_f16)                                                               */ \
  /*_(vdivq_f16)                                                              */ \
  /*_(vfma_f16)                                                          */      \
  /*_(vfmaq_f16)                                                         */      \
  /*_(vfms_f16)                                                          */      \
  /*_(vfmsq_f16)                                                         */      \
  /*_(vfma_lane_f16)                                                          */ \
  /*_(vfmaq_lane_f16)                                                         */ \
  /*_(vfma_laneq_f16)                                                         */ \
  /*_(vfmaq_laneq_f16)                                                        */ \
  /*_(vfma_n_f16)                                                             */ \
  /*_(vfmaq_n_f16)                                                            */ \
  /*_(vfmah_lane_f16)                                                         */ \
  /*_(vfmah_laneq_f16)                                                        */ \
  /*_(vfms_lane_f16)                                                          */ \
  /*_(vfmsq_lane_f16)                                                         */ \
  /*_(vfms_laneq_f16)                                                         */ \
  /*_(vfmsq_laneq_f16)                                                        */ \
  /*_(vfms_n_f16)                                                             */ \
  /*_(vfmsq_n_f16)                                                            */ \
  /*_(vfmsh_lane_f16)                                                         */ \
  /*_(vfmsh_laneq_f16)                                                        */ \
  /*_(vmax_f16)                                                          */      \
  /*_(vmaxq_f16)                                                         */      \
  /*_(vmaxnm_f16)                                                        */      \
  /*_(vmaxnmq_f16)                                                       */      \
  /*_(vmin_f16)                                                          */      \
  /*_(vminq_f16)                                                         */      \
  /*_(vminnm_f16)                                                        */      \
  /*_(vminnmq_f16)                                                       */      \
  /*_(vmul_f16)                                                          */      \
  /*_(vmul_lane_f16)                                                     */      \
  /*_(vmul_n_f16)                                                        */      \
  /*_(vmulq_f16)                                                         */      \
  /*_(vmulx_f16)                                                              */ \
  /*_(vmulxq_f16)                                                             */ \
  /*_(vmulq_lane_f16)                                                    */      \
  /*_(vmul_laneq_f16)                                                         */ \
  /*_(vmulq_laneq_f16)                                                        */ \
  /*_(vmulq_n_f16)                                                       */      \
  /*_(vmulh_lane_f16)                                                         */ \
  /*_(vmulh_laneq_f16)                                                        */ \
  /*_(vmulx_lane_f16)                                                         */ \
  /*_(vmulxq_lane_f16)                                                        */ \
  /*_(vmulx_laneq_f16)                                                        */ \
  /*_(vmulxq_laneq_f16)                                                       */ \
  /*_(vmulx_n_f16)                                                            */ \
  /*_(vmulxq_n_f16)                                                           */ \
  /*_(vmulxh_lane_f16)                                                        */ \
  /*_(vmulxh_laneq_f16)                                                       */ \
  /*_(vmaxv_f16)                                                              */ \
  /*_(vmaxvq_f16)                                                             */ \
  /*_(vminv_f16)                                                              */ \
  /*_(vminvq_f16)                                                             */ \
  /*_(vmaxnmv_f16)                                                            */ \
  /*_(vmaxnmvq_f16)                                                           */ \
  /*_(vminnmv_f16)                                                            */ \
  /*_(vminnmvq_f16)                                                           */ \
  /*_(vneg_f16)                                                          */      \
  /*_(vnegq_f16)                                                         */      \
  /*_(vpadd_f16)                                                         */      \
  /*_(vpaddq_f16)                                                             */ \
  /*_(vpmax_f16)                                                         */      \
  /*_(vpmaxq_f16)                                                             */ \
  /*_(vpmaxnm_f16)                                                            */ \
  /*_(vpmaxnmq_f16)                                                           */ \
  /*_(vpmin_f16)                                                         */      \
  /*_(vpminq_f16)                                                             */ \
  /*_(vpminnm_f16)                                                            */ \
  /*_(vpminnmq_f16)                                                           */ \
  /*_(vrecpe_f16)                                                        */      \
  /*_(vrecpeq_f16)                                                       */      \
  /*_(vrnd_f16)                                                          */      \
  /*_(vrndq_f16)                                                         */      \
  /*_(vrnda_f16)                                                         */      \
  /*_(vrndaq_f16)                                                        */      \
  /*_(vrndi_f16)                                                              */ \
  /*_(vrndiq_f16)                                                             */ \
  /*_(vrndm_f16)                                                         */      \
  /*_(vrndmq_f16)                                                        */      \
  /*_(vrndn_f16)                                                         */      \
  /*_(vrndnq_f16)                                                        */      \
  /*_(vrndp_f16)                                                         */      \
  /*_(vrndpq_f16)                                                        */      \
  /*_(vrndx_f16)                                                         */      \
  /*_(vrndxq_f16)                                                        */      \
  /*_(vrsqrte_f16)                                                       */      \
  /*_(vrsqrteq_f16)                                                      */      \
  /*_(vsqrt_f16)                                                              */ \
  /*_(vsqrtq_f16)                                                             */ \
  /*_(vrecps_f16)                                                        */      \
  /*_(vrecpsq_f16)                                                       */      \
  /*_(vrsqrts_f16)                                                       */      \
  /*_(vrsqrtsq_f16)                                                      */      \
  /*_(vsub_f16)                                                          */      \
  /*_(vsubq_f16)                                                         */      \
  /* Half-precision data processing intrinsics. */                               \
  /*_(vbsl_f16)                                                          */      \
  /*_(vbslq_f16)                                                         */      \
  /*_(vdup_n_f16)                                                        */      \
  /*_(vdupq_n_f16)                                                       */      \
  /*_(vdup_lane_f16)                                                     */      \
  /*_(vdupq_lane_f16)                                                    */      \
  /*_(vext_f16)                                                          */      \
  /*_(vextq_f16)                                                         */      \
  /*_(vmov_n_f16)                                                        */      \
  /*_(vmovq_n_f16)                                                       */      \
  /*_(vrev64_f16)                                                        */      \
  /*_(vrev64q_f16)                                                       */      \
  /*_(vzip1_f16)                                                              */ \
  /*_(vzip1q_f16)                                                             */ \
  /*_(vzip2_f16)                                                              */ \
  /*_(vzip2q_f16)                                                             */ \
  /*_(vuzp1_f16)                                                              */ \
  /*_(vuzp1q_f16)                                                             */ \
  /*_(vuzp2_f16)                                                              */ \
  /*_(vuzp2q_f16)                                                             */ \
  /*_(vtrn1_f16)                                                              */ \
  /*_(vtrn1q_f16)                                                             */ \
  /*_(vtrn2_f16)                                                              */ \
  /*_(vtrn2q_f16)                                                             */ \
  /*_(vdup_laneq_f16)                                                         */ \
  /*_(vdupq_laneq_f16)                                                        */ \
  /*_(vduph_lane_f16)                                                         */ \
  /*_(vduph_laneq_f16)                                                        */ \
  /*_(vtrn_f16)                                                          */      \
  /*_(vtrnq_f16)                                                         */      \
  /*_(vuzp_f16)                                                          */      \
  /*_(vuzpq_f16)                                                         */      \
  /*_(vzip_f16)                                                          */      \
  /*_(vzipq_f16)                                                         */      \
  /* AdvSIMD Dot Product intrinsics. */                                          \
  /*_(vdot_u32)                                                               */ \
  /*_(vdotq_u32)                                                              */ \
  /*_(vdot_s32)                                                               */ \
  /*_(vdotq_s32)                                                              */ \
  /*_(vdot_lane_u32)                                                          */ \
  /*_(vdotq_lane_u32)                                                         */ \
  /*_(vdot_lane_s32)                                                          */ \
  /*_(vdotq_lane_s32)                                                         */ \
  /*_(vsha512hq_u64)                                                          */ \
  /*_(vsha512h2q_u64)                                                         */ \
  /*_(vsha512su0q_u64)                                                        */ \
  /*_(vsha512su1q_u64)                                                        */ \
  /*_(veor3q_u8)                                                              */ \
  /*_(veor3q_u16)                                                             */ \
  /*_(veor3q_u32)                                                             */ \
  /*_(veor3q_u64)                                                             */ \
  /*_(veor3q_s8)                                                              */ \
  /*_(veor3q_s16)                                                             */ \
  /*_(veor3q_s32)                                                             */ \
  /*_(veor3q_s64)                                                             */ \
  /*_(vrax1q_u64)                                                             */ \
  /*_(vxarq_u64)                                                              */ \
  /*_(vbcaxq_u8)                                                              */ \
  /*_(vbcaxq_u16)                                                             */ \
  /*_(vbcaxq_u32)                                                             */ \
  /*_(vbcaxq_u64)                                                             */ \
  /*_(vbcaxq_s8)                                                              */ \
  /*_(vbcaxq_s16)                                                             */ \
  /*_(vbcaxq_s32)                                                             */ \
  /*_(vbcaxq_s64)                                                             */ \
  /*_(vsm3ss1q_u32)                                                           */ \
  /*_(vsm3tt1aq_u32)                                                          */ \
  /*_(vsm3tt1bq_u32)                                                          */ \
  /*_(vsm3tt2aq_u32)                                                          */ \
  /*_(vsm3tt2bq_u32)                                                          */ \
  /*_(vsm3partw1q_u32)                                                        */ \
  /*_(vsm3partw2q_u32)                                                        */ \
  /*_(vsm4eq_u32)                                                             */ \
  /*_(vsm4ekeyq_u32)                                                          */ \
  /*_(vdot_laneq_u32)                                                         */ \
  /*_(vdotq_laneq_u32)                                                        */ \
  /*_(vdot_laneq_s32)                                                         */ \
  /*_(vdotq_laneq_s32)                                                        */ \
  /*_(vfmlal_low_f16)                                                    */      \
  /*_(vfmlsl_low_f16)                                                    */      \
  /*_(vfmlal_high_f16)                                                   */      \
  /*_(vfmlsl_high_f16)                                                   */      \
  /*_(vfmlalq_low_f16)                                                   */      \
  /*_(vfmlslq_low_f16)                                                   */      \
  /*_(vfmlalq_high_f16)                                                  */      \
  /*_(vfmlslq_high_f16)                                                  */      \
  /*_(vfmlal_lane_low_f16)                                               */      \
  /*_(vfmlal_lane_high_f16)                                              */      \
  /*_(vfmlalq_laneq_low_f16)                                             */      \
  /*_(vfmlalq_lane_low_f16)                                              */      \
  /*_(vfmlal_laneq_low_f16)                                              */      \
  /*_(vfmlalq_laneq_high_f16)                                            */      \
  /*_(vfmlalq_lane_high_f16)                                             */      \
  /*_(vfmlal_laneq_high_f16)                                             */      \
  /*_(vfmlsl_lane_low_f16)                                               */      \
  /*_(vfmlsl_lane_high_f16)                                              */      \
  /*_(vfmlslq_laneq_low_f16)                                             */      \
  /*_(vfmlslq_lane_low_f16)                                              */      \
  /*_(vfmlsl_laneq_low_f16)                                              */      \
  /*_(vfmlslq_laneq_high_f16)                                            */      \
  /*_(vfmlslq_lane_high_f16)                                             */      \
  /*_(vfmlsl_laneq_high_f16)                                             */      \
  /* AdvSIMD Complex numbers intrinsics. */                                      \
  /*_(vcadd_rot90_f16)                                                   */      \
  /*_(vcaddq_rot90_f16)                                                  */      \
  /*_(vcadd_rot270_f16)                                                  */      \
  /*_(vcaddq_rot270_f16)                                                 */      \
  /*_(vcmla_f16)                                                         */      \
  /*_(vcmlaq_f16)                                                        */      \
  /*_(vcmla_lane_f16)                                                    */      \
  /*_(vcmla_laneq_f16)                                                   */      \
  /*_(vcmlaq_lane_f16)                                                   */      \
  /*_(vcmlaq_laneq_f16)                                                  */      \
  /*_(vcmla_rot90_f16)                                                   */      \
  /*_(vcmlaq_rot90_f16)                                                  */      \
  /*_(vcmla_rot90_lane_f16)                                              */      \
  /*_(vcmla_rot90_laneq_f16)                                             */      \
  /*_(vcmlaq_rot90_lane_f16)                                             */      \
  /*_(vcmlaq_rot90_laneq_f16)                                            */      \
  /*_(vcmla_rot180_f16)                                                  */      \
  /*_(vcmlaq_rot180_f16)                                                 */      \
  /*_(vcmla_rot180_lane_f16)                                             */      \
  /*_(vcmla_rot180_laneq_f16)                                            */      \
  /*_(vcmlaq_rot180_lane_f16)                                            */      \
  /*_(vcmlaq_rot180_laneq_f16)                                           */      \
  /*_(vcmla_rot270_f16)                                                  */      \
  /*_(vcmlaq_rot270_f16)                                                 */      \
  /*_(vcmla_rot270_lane_f16)                                             */      \
  /*_(vcmla_rot270_laneq_f16)                                            */      \
  /*_(vcmlaq_rot270_lane_f16)                                            */      \
  /*_(vcmlaq_rot270_laneq_f16)                                           */      \
  /*_(vcadd_rot90_f32)                                                        */ \
  /*_(vcaddq_rot90_f32)                                                       */ \
  /*_(vcaddq_rot90_f64)                                                       */ \
  /*_(vcadd_rot270_f32)                                                       */ \
  /*_(vcaddq_rot270_f32)                                                      */ \
  /*_(vcaddq_rot270_f64)                                                      */ \
  /*_(vcmla_f32)                                                              */ \
  /*_(vcmlaq_f32)                                                             */ \
  /*_(vcmlaq_f64)                                                             */ \
  /*_(vcmla_lane_f32)                                                         */ \
  /*_(vcmla_laneq_f32)                                                        */ \
  /*_(vcmlaq_lane_f32)                                                        */ \
  /*_(vcmlaq_laneq_f32)                                                       */ \
  /*_(vcmla_rot90_f32)                                                        */ \
  /*_(vcmlaq_rot90_f32)                                                       */ \
  /*_(vcmlaq_rot90_f64)                                                       */ \
  /*_(vcmla_rot90_lane_f32)                                                   */ \
  /*_(vcmla_rot90_laneq_f32)                                                  */ \
  /*_(vcmlaq_rot90_lane_f32)                                                  */ \
  /*_(vcmlaq_rot90_laneq_f32)                                                 */ \
  /*_(vcmla_rot180_f32)                                                       */ \
  /*_(vcmlaq_rot180_f32)                                                      */ \
  /*_(vcmlaq_rot180_f64)                                                      */ \
  /*_(vcmla_rot180_lane_f32)                                                  */ \
  /*_(vcmla_rot180_laneq_f32)                                                 */ \
  /*_(vcmlaq_rot180_lane_f32)                                                 */ \
  /*_(vcmlaq_rot180_laneq_f32)                                                */ \
  /*_(vcmla_rot270_f32)                                                       */ \
  /*_(vcmlaq_rot270_f32)                                                      */ \
  /*_(vcmlaq_rot270_f64)                                                      */ \
  /*_(vcmla_rot270_lane_f32)                                                  */ \
  /*_(vcmla_rot270_laneq_f32)                                                 */ \
  /*_(vcmlaq_rot270_lane_f32)                                                 */ \
  /*_(vcmlaq_rot270_laneq_f32)                                                */ \
  /*_(vrnd32z_f32)                                                            */ \
  /*_(vrnd32zq_f32)                                                           */ \
  /*_(vrnd32z_f64)                                                            */ \
  /*_(vrnd32zq_f64)                                                           */ \
  /*_(vrnd64z_f32)                                                            */ \
  /*_(vrnd64zq_f32)                                                           */ \
  /*_(vrnd64z_f64)                                                            */ \
  /*_(vrnd64zq_f64)                                                           */ \
  /*_(vrnd32x_f32)                                                            */ \
  /*_(vrnd32xq_f32)                                                           */ \
  /*_(vrnd32x_f64)                                                            */ \
  /*_(vrnd32xq_f64)                                                           */ \
  /*_(vrnd64x_f32)                                                            */ \
  /*_(vrnd64xq_f32)                                                           */ \
  /*_(vrnd64x_f64)                                                            */ \
  /*_(vrnd64xq_f64)                                                           */ \
  /*_(vmmlaq_s32)                                                             */ \
  /*_(vmmlaq_u32)                                                             */ \
  /*_(vusmmlaq_s32)                                                           */ \
  /* AdvSIMD Matrix Multiply-Accumulate and Dot Product intrinsics. */           \
  /*_(vusdot_s32)                                                             */ \
  /*_(vusdotq_s32)                                                            */ \
  /*_(vusdot_lane_s32)                                                        */ \
  /*_(vusdotq_lane_s32)                                                       */ \
  /*_(vsudot_lane_s32)                                                        */ \
  /*_(vsudotq_lane_s32)                                                       */ \
  /*_(vusdot_laneq_s32)                                                       */ \
  /*_(vusdotq_laneq_s32)                                                      */ \
  /*_(vsudot_laneq_s32)                                                       */ \
  /*_(vsudotq_laneq_s32)                                                      */ \
  /*_(vcreate_bf16)                                                           */ \
  /*_(vdup_n_bf16)                                                            */ \
  /*_(vdupq_n_bf16)                                                           */ \
  /*_(vdup_lane_bf16)                                                         */ \
  /*_(vdupq_lane_bf16)                                                        */ \
  /*_(vdup_laneq_bf16)                                                        */ \
  /*_(vdupq_laneq_bf16)                                                       */ \
  /*_(vcombine_bf16)                                                          */ \
  /*_(vget_high_bf16)                                                         */ \
  /*_(vget_low_bf16)                                                          */ \
  /*_(vget_lane_bf16)                                                         */ \
  /*_(vgetq_lane_bf16)                                                        */ \
  /*_(vset_lane_bf16)                                                         */ \
  /*_(vsetq_lane_bf16)                                                        */ \
  /*_(vduph_lane_bf16)                                                        */ \
  /*_(vduph_laneq_bf16)                                                       */ \
  /*_(vld1_bf16)                                                              */ \
  /*_(vld1q_bf16)                                                             */ \
  /*_(vld1_lane_bf16)                                                         */ \
  /*_(vld1q_lane_bf16)                                                        */ \
  /*_(vld1_dup_bf16)                                                          */ \
  /*_(vld1q_dup_bf16)                                                         */ \
  /*_(vst1_bf16)                                                              */ \
  /*_(vst1q_bf16)                                                             */ \
  /*_(vst1_lane_bf16)                                                         */ \
  /*_(vst1q_lane_bf16)                                                        */ \
  /*_(vld2_bf16)                                                              */ \
  /*_(vld2q_bf16)                                                             */ \
  /*_(vld3_bf16)                                                              */ \
  /*_(vld3q_bf16)                                                             */ \
  /*_(vld4_bf16)                                                              */ \
  /*_(vld4q_bf16)                                                             */ \
  /*_(vld2_dup_bf16)                                                          */ \
  /*_(vld2q_dup_bf16)                                                         */ \
  /*_(vld3_dup_bf16)                                                          */ \
  /*_(vld3q_dup_bf16)                                                         */ \
  /*_(vld4_dup_bf16)                                                          */ \
  /*_(vld4q_dup_bf16)                                                         */ \
  /*_(vst2_bf16)                                                              */ \
  /*_(vst2q_bf16)                                                             */ \
  /*_(vst3_bf16)                                                              */ \
  /*_(vst3q_bf16)                                                             */ \
  /*_(vst4_bf16)                                                              */ \
  /*_(vst4q_bf16)                                                             */ \
  /*_(vld2_lane_bf16)                                                         */ \
  /*_(vld2q_lane_bf16)                                                        */ \
  /*_(vld3_lane_bf16)                                                         */ \
  /*_(vld3q_lane_bf16)                                                        */ \
  /*_(vld4_lane_bf16)                                                         */ \
  /*_(vld4q_lane_bf16)                                                        */ \
  /*_(vst2_lane_bf16)                                                         */ \
  /*_(vst2q_lane_bf16)                                                        */ \
  /*_(vst3_lane_bf16)                                                         */ \
  /*_(vst3q_lane_bf16)                                                        */ \
  /*_(vst4_lane_bf16)                                                         */ \
  /*_(vst4q_lane_bf16)                                                        */ \
  /*_(vst1_bf16_x2)                                                           */ \
  /*_(vst1q_bf16_x2)                                                          */ \
  /*_(vst1_bf16_x3)                                                           */ \
  /*_(vst1q_bf16_x3)                                                          */ \
  /*_(vst1_bf16_x4)                                                           */ \
  /*_(vst1q_bf16_x4)                                                          */ \
  /*_(vld1_bf16_x2)                                                           */ \
  /*_(vld1q_bf16_x2)                                                          */ \
  /*_(vld1_bf16_x3)                                                           */ \
  /*_(vld1q_bf16_x3)                                                          */ \
  /*_(vld1_bf16_x4)                                                           */ \
  /*_(vld1q_bf16_x4)                                                          */ \
  /*_(vreinterpret_bf16_s8)                                                   */ \
  /*_(vreinterpret_bf16_s16)                                                  */ \
  /*_(vreinterpret_bf16_s32)                                                  */ \
  /*_(vreinterpret_bf16_f32)                                                  */ \
  /*_(vreinterpret_bf16_u8)                                                   */ \
  /*_(vreinterpret_bf16_u16)                                                  */ \
  /*_(vreinterpret_bf16_u32)                                                  */ \
  /*_(vreinterpret_bf16_p8)                                                   */ \
  /*_(vreinterpret_bf16_p16)                                                  */ \
  /*_(vreinterpret_bf16_u64)                                                  */ \
  /*_(vreinterpret_bf16_s64)                                                  */ \
  /*_(vreinterpretq_bf16_s8)                                                  */ \
  /*_(vreinterpretq_bf16_s16)                                                 */ \
  /*_(vreinterpretq_bf16_s32)                                                 */ \
  /*_(vreinterpretq_bf16_f32)                                                 */ \
  /*_(vreinterpretq_bf16_u8)                                                  */ \
  /*_(vreinterpretq_bf16_u16)                                                 */ \
  /*_(vreinterpretq_bf16_u32)                                                 */ \
  /*_(vreinterpretq_bf16_p8)                                                  */ \
  /*_(vreinterpretq_bf16_p16)                                                 */ \
  /*_(vreinterpretq_bf16_u64)                                                 */ \
  /*_(vreinterpretq_bf16_s64)                                                 */ \
  /*_(vreinterpret_bf16_f64)                                                  */ \
  /*_(vreinterpretq_bf16_f64)                                                 */ \
  /*_(vreinterpret_bf16_p64)                                                  */ \
  /*_(vreinterpretq_bf16_p64)                                                 */ \
  /*_(vreinterpretq_bf16_p128)                                                */ \
  /*_(vreinterpret_s8_bf16)                                                   */ \
  /*_(vreinterpret_s16_bf16)                                                  */ \
  /*_(vreinterpret_s32_bf16)                                                  */ \
  /*_(vreinterpret_f32_bf16)                                                  */ \
  /*_(vreinterpret_u8_bf16)                                                   */ \
  /*_(vreinterpret_u16_bf16)                                                  */ \
  /*_(vreinterpret_u32_bf16)                                                  */ \
  /*_(vreinterpret_p8_bf16)                                                   */ \
  /*_(vreinterpret_p16_bf16)                                                  */ \
  /*_(vreinterpret_u64_bf16)                                                  */ \
  /*_(vreinterpret_s64_bf16)                                                  */ \
  /*_(vreinterpret_f64_bf16)                                                  */ \
  /*_(vreinterpret_p64_bf16)                                                  */ \
  /*_(vreinterpretq_s8_bf16)                                                  */ \
  /*_(vreinterpretq_s16_bf16)                                                 */ \
  /*_(vreinterpretq_s32_bf16)                                                 */ \
  /*_(vreinterpretq_f32_bf16)                                                 */ \
  /*_(vreinterpretq_u8_bf16)                                                  */ \
  /*_(vreinterpretq_u16_bf16)                                                 */ \
  /*_(vreinterpretq_u32_bf16)                                                 */ \
  /*_(vreinterpretq_p8_bf16)                                                  */ \
  /*_(vreinterpretq_p16_bf16)                                                 */ \
  /*_(vreinterpretq_u64_bf16)                                                 */ \
  /*_(vreinterpretq_s64_bf16)                                                 */ \
  /*_(vreinterpretq_f64_bf16)                                                 */ \
  /*_(vreinterpretq_p64_bf16)                                                 */ \
  /*_(vreinterpretq_p128_bf16)                                                */ \
  /*_(vcvt_f32_bf16)                                                          */ \
  /*_(vcvtq_low_f32_bf16)                                                     */ \
  /*_(vcvtq_high_f32_bf16)                                                    */ \
  /*_(vcvt_bf16_f32)                                                          */ \
  /*_(vcvtq_low_bf16_f32)                                                     */ \
  /*_(vcvtq_high_bf16_f32)                                                    */ \
  /*_(vcvth_bf16_f32)                                                         */ \
  /*_(vcvtah_f32_bf16)                                                        */ \
  /*_(vcopy_lane_bf16)                                                        */ \
  /*_(vcopyq_lane_bf16)                                                       */ \
  /*_(vcopy_laneq_bf16)                                                       */ \
  /*_(vcopyq_laneq_bf16)                                                      */ \
  /*_(vbfdot_f32)                                                             */ \
  /*_(vbfdotq_f32)                                                            */ \
  /*_(vbfdot_lane_f32)                                                        */ \
  /*_(vbfdotq_laneq_f32)                                                      */ \
  /*_(vbfdot_laneq_f32)                                                       */ \
  /*_(vbfdotq_lane_f32)                                                       */ \
  /*_(vbfmmlaq_f32)                                                           */ \
  /*_(vbfmlalbq_f32)                                                          */ \
  /*_(vbfmlaltq_f32)                                                          */ \
  /*_(vbfmlalbq_lane_f32)                                                     */ \
  /*_(vbfmlalbq_laneq_f32)                                                    */ \
  /*_(vbfmlaltq_lane_f32)                                                     */ \
  /*_(vbfmlaltq_laneq_f32)                                                    */ \
  _(last) /* This indicates the end of macros */

namespace NEON2RVV {
// The way unit tests are implemented is that 10,000 random floating point and
// integer vec4 numbers are generated as sample data.
//
// A short C implementation of every intrinsic is implemented and compared to
// the actual expected results from the corresponding NEON intrinsic against all
// of the 10,000 randomized input vectors. When running on ARM, then the results
// are compared to the NEON approximate version.
static const char* instruction_string[] __attribute__((unused)) = {
#define _(x) #x,
    INTRIN_LIST
#undef _
};

enum INSTRUCTION_TEST {
#define _(x) it_##x,
  INTRIN_LIST
#undef _
};

class NEON2RVV_TEST {
 public:
  static NEON2RVV_TEST* create(void);  // create the test.

  // Run test of this instruction;
  // Passed: TEST_SUCCESS (1)
  // Failed: TEST_FAIL (0)
  // Unimplemented: TEST_UNIMPL (-1)
  virtual result_t run_test(INSTRUCTION_TEST test) = 0;
  virtual void release(void) = 0;
};

}  // namespace NEON2RVV

#endif  // NEON2RVV_TEST_H

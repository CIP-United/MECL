/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        BayesFunctions.c
 * Description:  Combination of all distance function source files.
 *
 * $Date:        16. March 2020
 * $Revision:    V1.0.0
 *
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2020 ARM Limited or its affiliates. All rights reserved.
 * Copyright (C) 2023 CIP United Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mips_boolean_distance.c"
#include "mips_braycurtis_distance_f32.c"
#include "mips_canberra_distance_f32.c"
#include "mips_chebyshev_distance_f32.c"
#include "mips_chebyshev_distance_f64.c"
#include "mips_cityblock_distance_f32.c"
#include "mips_cityblock_distance_f64.c"
#include "mips_correlation_distance_f32.c"
#include "mips_cosine_distance_f32.c"
#include "mips_cosine_distance_f64.c"
#include "mips_dice_distance.c"
#include "mips_euclidean_distance_f32.c"
#include "mips_euclidean_distance_f64.c"
#include "mips_hamming_distance.c"
#include "mips_jaccard_distance.c"
#include "mips_jensenshannon_distance_f32.c"
#include "mips_kulsinski_distance.c"
#include "mips_minkowski_distance_f32.c"
#include "mips_rogerstanimoto_distance.c"
#include "mips_russellrao_distance.c"
#include "mips_sokalmichener_distance.c"
#include "mips_sokalsneath_distance.c"
#include "mips_yule_distance.c"
#include "mips_dtw_distance_f32.c"
#include "mips_dtw_path_f32.c"
#include "mips_dtw_init_window_q7.c"
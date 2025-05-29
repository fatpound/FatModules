/*******************************************************************************/
/*                                                                             */
/*                 :::::::                                                     */
/*               :+:    :+:            ::                                      */
/*              +:+            :+     +#                                       */
/*             +#+            +#pL+++##+##++:                                  */
/*            +#+         ++#+##+++ uﬂ#+               :::::::        :::      */
/*           #+#     #+#     #+      ##              :+:    :+:     :+:        */
/*            ########      ##                            +:+     +:++         */
/*                                                      +#+      +#+  +:+      */
/*                                                    +#+      +#+#    #+#+    */
/*  <> FatPound.ixx                                 #+#         #+#   #+#      */
/*                                                ########:#      ##.tr        */
/*                                                                             */
/*  >< Created: --/--/---- ??:??:??                                            */
/*  >< Updated: 01/05/2025 11:54:10                                            */
/*  >< By: fatpound                                                            */
/*                                                                             */
/*******************************************************************************/

//           //
// fatpound* //
//           //

module;

export module FatPound;

export import FatPound.Algorithm;
export import FatPound.Automata;
export import FatPound.Bit;
export import FatPound.Concurrency;
export import FatPound.Cryptography;
export import FatPound.DSA;
export import FatPound.File;
export import FatPound.IO;
export import FatPound.Math;
export import FatPound.Memory;
export import FatPound.Random;
export import FatPound.Traits;
export import FatPound.Utility;

#if FAT_BUILDING_WITH_MSVC
    export import FatPound.Win32;
#endif

module : private;

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
/*  >< Updated: 19/07/2025 23:40:17                                            */
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
export import FatPound.Colors;
export import FatPound.Concurrency;
export import FatPound.Cryptography;
export import FatPound.DSA;
export import FatPound.File;
export import FatPound.Geometry;
export import FatPound.Graph;
export import FatPound.IO;
export import FatPound.Math;
export import FatPound.Memory;
export import FatPound.Random;
export import FatPound.Traits;
export import FatPound.Utility;

#ifdef FATLIB_BUILDING_WITH_MSVC
    export import FatPound.Win32;
#endif

export import FatX;

// module : private;

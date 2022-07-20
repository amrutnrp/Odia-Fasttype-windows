( function ( $ ) {
	'use strict';

	var orFastType = {
		id: 'or-fasttype',
		name: 'ଫାଷ୍ଟ୍‍ଟାଇପ୍',
		description: 'Odia FastType input method',
		date: '2021-10-15',
		URL: 'http://github.com/wikimedia/jquery.ime',
		author: ' Amrutnarayan Panigrahi',
		license: 'GPLv3',
		version: '0.1',
		contextLength: 5,
		maxKeyLength: 2,
		patterns: [

			//[ '\\\\([A-Za-z\\>_~\\.0-9])', '\\\\', '$1' ],  // preserve after typing '\'

			[ 'f', '୍' ],

			[ 'h', 'ହ' ],
			[ '‍h', 'ହ' ], // ZWJ
			
					
			// [ 'a', 'ଅ' ],
			// [ 'ଅa', 'ଆ' ], //  aa
			// [ 'A', 'ଆ' ],	// cap
			// [ 'ଅ/', 'ଆ' ], 	 //  letter 1- > 2
			// [ 'ାa', 'ା' ], 	 //  matra 1- > 2 
			// [ 'ାa', 'ଆ' ],  //matra -> letter 1
			// [ 'ାo', 'ଅ' ],  //matra -> letter 2
			// [ '‍a', 'ଆ' ], // ZWJ
			// [ 'a', 'ା' ],	 // many conditions   #-		
//			[ 'ଆa', 'ଆ' ], 	
//			[ '([ଇ-ଔ])a' , '$1ଆ'],  		
//			[ 'A', 'ଅ' ],
//			[ '\ a', ' ଆ' ],	
	
			[ 'a', 'ା' ],	 // many conditions   #-	
			[ 'a', 'ଅ' ],
			[ 'ଅa', 'ଆ' ], //  aa
			[ 'A', 'ଆ' ],	// cap
			[ 'ଅ/', 'ଆ' ], 	 //  letter 1- > 2
			[ 'ାa', 'ା' ], 	 //  matra 1- > 2 
			[ '‍a', 'ଆ' ], // ZWJ
			 
			
			[ 'e', 'େ' ], // many conditions   #- 
			[ 'e', 'ଏ' ],
			[ 'E', 'ଐ' ],	 // cap
			[ 'ଏ/', 'ଐ' ], //  letter 1- > 2
			[ 'େ/', 'ୈ' ],  //  matra 1- > 2 
			[ '‍e', 'ଏ' ], // ZWJ	

			[ 'i', 'ି' ], // many conditions   #- 					
			['i', 'ଇ']
			[ 'I', 'ଈ' ], //cap
			[ 'ଇ/', 'ଈ' ], //  letter 1- > 2
			[ 'ି/', 'ୀ' ],  //  matra 1- > 2 			
			[ '‍i', 'ଇ' ], // ZWJ	

			[ 'o', 'ୋ' ], // many conditions   #- 
			[ 'o', 'ଓ' ],
			[ 'O', 'ଔ' ], //cap
			[ 'ଓ/', 'ଔ' ], //  letter 1- > 2
			[ 'ୋ/', 'ୌ' ],  //  matra 1- > 2 			
			[ '‍o', 'ଓ' ], // ZWJ	
			

			[ 'u', 'ୁ' ], // many conditions   #- 
			[ 'u', 'ଉ' ],	
			[ 'U', 'ଊ' ],
			[ 'ଉ/', 'ଊ' ], //  letter 1- > 2
			[ 'ୁ/', 'ୂ' ],  //  matra 1- > 2 				
			[ '‍u', 'ଉ' ],// ZWJ	
			
			


			//pronounce odia
			
			[ 'ାa', 'ଆ' ],  //matra -> letter 1
			[ 'ାo', 'ଅ' ],  //matra -> letter 2			
			[ 'ାi', 'ୈ' ],
			[ 'ାu', 'ୌ' ],
			[ 'େi', 'ୈ' ],
			[ 'ୋu', 'ୌ' ],
			
			//pronounce english 
			[ 'େe', 'ୀ' ],
			[ 'ୋo', 'ୂ' ], 
			[ 'ିi', 'ୀ' ],
			[ 'ୁu', 'ୂ' ],		
			
			//only matra
			
			[ 'ଅf', 'ା' ],
			[ 'ଏf', 'େ' ],
			[ 'ଇf', 'ି' ],
			[ 'ଓf', 'ୋ' ],
			[ 'ଉf', 'ୁ' ],
			
// special characters - 

			['0','୦'],
			['1','୧'],
			['2','୨'],
			['3','୩'],
			['4','୪'],
			['5','୫'],
			['6','୬'],
			['7','୭'],
			['8','୮'],
			['9','୯'],
			
			['\\.',' ।'],
			['~','୰'],
			['\\[','‍']
			
            ['`' , '୍' ],
			[ '।\\.', '॥' ],
			
// special characters - end 
// consonants start

		    //-a
			[ 'b', 'ବ' ],                  //#+
			[ 'c', 'ଚ' ],                  //#+
			[ 'd', 'ଦ' ],                  //#+
			//-e                         //#+
			[ 'g', 'ଗ' ],                  //#+
			//-i                         //#+
			[ 'j', 'ଜ' ],                  //#+
			[ 'k', 'କ' ],                  //#+
			[ 'l', 'ଲ' ],                  //#+
			[ 'm', 'ମ' ],                  //#+
			[ 'n', 'ନ' ],                  //#+
			//-o                         //#+
			[ 'p', 'ପ' ],                  //#+
			[ 'q', 'ତ' ],                  //#+
			[ 'r', 'ର' ],                  //#+
			[ 's', 'ସ' ],                  //#+
			[ 't', 'ଟ' ],                  //#+
			//-u                         //#+
			[ 'v', 'ଡ' ],                  //#+
			[ 'w', 'ୱ' ],                  //#+
			[ 'x', 'କ୍ଷ' ],                  //#+
			[ 'y', 'ୟ' ],                  //#+
			[ 'z', 'ଯ' ],                  //#+
										 //#+

			//A
			[ 'B', 'ମ୍ବ' ],                   //#+
			[ 'C', 'ଞ୍ଚ' ],                   //#+
			[ 'D', 'ନ୍ଦ' ],                   //#+
			//E                            //#+
			[ 'F', '଼' ],                   //#+
			[ 'G', 'ଙ୍ଗ' ],                   //#+
			[ 'H', 'ହ' ],                   //#+
			//E                            //#+
			[ 'J', 'ଞ୍ଜ' ],                   //#+
			[ 'K', 'ଙ୍କ' ],                   //#+
			[ 'L', 'ଳ' ],                   //#+
			[ 'M', 'ଂ' ],                   
			[ 'N', 'ଣ' ],                   //#+
			//O                            //#+
			[ 'P', 'ମ୍ପ' ],                   //#+
			[ 'Q', 'ନ୍ତ' ],                   //#+
			[ 'R', 'ୃ' ],                   
			[ 'S', 'ଷ' ],                   //#+
			[ 'T', 'ଣ୍ଟ' ],                   //#+
			// U                           //#+
			[ 'V', 'ଣ୍ଡ' ],                   //#+
			[ 'W', 'ଁ' ],                   
			[ 'X', 'ଢ଼' ],                   //#+
			[ 'Y', '୳' ],                   
			[ 'Z', 'ଡ଼' ],                   //#+


			// a
			[ 'ବh', 'ଭ' ],                   //#+
			[ 'ଚh', 'ଛ' ],                   //#+
			[ 'ଦh', 'ଧ' ],                   //#+
			// e                          / /#+
			[ 'ଗh', 'ଘ' ],                  //#+
			// i                          / /#+
			[ 'ଜh', 'ଝ' ],                   //#+
			[ 'କh', 'ଖ' ],                   //#+
			[ 'ଲh', 'ଲ୍ଲ' ],                  //#+
			// o                          / /#+
			[ 'ପh', 'ଫ' ],                  //#+
			[ 'ତh', 'ଥ' ],                   //#+
			[ 'ରh', 'ୠ' ],                  //#+
			[ 'ସh', 'ଶ' ],                   //#+
			[ 'ଟh', 'ଠ' ],                   //#+
			// u                          / /#+
			[ 'ଡh', 'ଢ' ],                   //#+
			[ 'ୱh', 'ଵ' ],                   //#+
										  //#+
			
// consonants  end
										 //#+
			[ 'ଚ/', 'ଞ' ],                   //#+
			[ 'ଗ/', 'ଙ' ],                   //#+
			[ 'ଜ/', 'ଞ' ],                   //#+
			[ 'କ/', 'ଙ' ],                   //#+
			[ 'ଲ/', 'ଌ' ],                   //#+
			[ 'ନ/', 'ଣ୍ଣ' ],                   //#+
			[ 'ର/', 'ୃ' ],                   //#+
			[ 'ସ/', 'ଷ୍ଣ' ],                   //#+
										 //#+
			[ 'ହ/', 'ଃ' ],                  //#+
			//  [ 'ସf', 'ୡ' ],   ?                  //            #+
			[ 'କ୍ଷ/', 'ଜ୍ଞ' ],                   //#+
			                           //#+

//slash end 			

			// [ 'କ୍ଷh', '୵' ],
			// [ 'ଯh', 'ଽ' ],
			// [ 'ାf', '୲' ],
			// [ 'ସf', 'ୡ' ],
			// [ 'ଯf', '.' ],
			// ['h', 'ହ' ],


		]
	};

	$.ime.register( orFastType );
}( jQuery ) );

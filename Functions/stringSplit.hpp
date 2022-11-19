

//----------------------------------------------------------------
//						stringSplit Function
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

split a string by a delimiter and return an array of the split words

*/

/* Function Input

std::string inputString

char delimiter

*/


/*Function Output

std::vector 

*/

std::vector<std::string> stringSplit(std::string inputString, char delimiter){

	std::vector<std::string> outputWords;

	std::string word;

	for(int i = 0; i < inputString.length(); i++){

		word += inputString[i];

		if(inputString[i] == delimiter){
			
			outputWords.push_back(word);

			word = "";
		
		}
	}

	outputWords.push_back(word);

	return outputWords;
	
}





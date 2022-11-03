
#include "Utilities.h" 

#include <algorithm> 

namespace neu{

	std::string ToLower(const std::string& str){

		std::string lower = str;
		
		std::transform(lower.begin(), lower.end(), lower.begin(),[](unsigned char c) { return std::tolower(c); });
	
		return lower;

	}

	std::string ToUpper(const std::string& str){

		std::string upper = str;
		
		std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) { return std::toupper(c); }); //AaBb pIzZZa -> aabb pizzza
	
		return upper;

	}

	bool CompareIgnoreCase(const std::string& str1, const std::string& str2){

		if (str1.length() != str2.length()) {

			return false;

		}else if (str1 != str2) {

			return false;

		}

		return true;

	}

}

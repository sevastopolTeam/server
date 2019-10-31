#pragma once

#include <string>

using TString = std::string;

namespace NString {
	int ToInt(const TString& s) {
		int res = 0;
		for (int i = 0; i < s.size(); i++) {
			res = res * 10 + s[i] - '0';
		}

		return res;
	}

	TString FromInt(const int value) {
		return std::to_string(value);
	}

	bool EndsWith(const TString& value, const TString& ending) {
		if (ending.size() > value.size()) {
			return false;
		}
		return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
	}

	bool IsVowel(const char c) {
		if (!isalpha(c)) {
			return false;
		}
		return tolower(c) == 'a' || tolower(c) == 'o' || tolower(c) == 'e' || tolower(c) == 'u'	|| tolower(c) == 'i';
	}

	bool IsConsonant(const char c) {
		if (!isalpha(c)) {
			return false;
		}

		return !IsVowel(c);
	}
};
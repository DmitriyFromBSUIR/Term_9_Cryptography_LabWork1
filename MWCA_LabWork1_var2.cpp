// MWCA_LabWork1_var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define LETTERSMAXCOUNT 16
#define LETTERSCOUNT 8
#define WORDSCOUNT 19
#define WORDSINCRYPTOTEXT 3
#define NUMSYSBUFFERSIZE 128
#define CRYPTOTEXT "111101101001101010110010011001101010010011000"

struct CodesOfLetters {
	unsigned int _maxCodesCount = 2 << (LETTERSCOUNT-1);
	char _letters[LETTERSMAXCOUNT] = { 'М', 'И', 'Ц', 'А', 'Р', 'Я', 'Т', 'У', 'м', 'и', 'ц', 'а', 'р', 'я', 'т', 'у' };
	int _letterCodes[LETTERSCOUNT][LETTERSCOUNT];
	vector<int> _codes; // list of all aviable codes for letters
	vector<vector<int>> _allCodesCombinations;
	vector<vector<string>> _allCodesCombinationsInBin;
	unsigned long int _combinationsCount = 0;

	//void codesVectorFillup(){
	CodesOfLetters() {
		for (size_t i = 0; i < LETTERSCOUNT; i++) {
			_codes.push_back(i);
		}
	}
	void lettersCodesInit() {
		for (size_t i = 0; i < LETTERSCOUNT; i++) {
			for (size_t j = 0; j < LETTERSCOUNT; j++) {
				//for (size_t k = 0; j < _maxCodesCount; j++)
					_letterCodes[i][j] = 0;
			}
		}
	}
	void allCodesPrint() {
		cout << "List of Letter's Codes:" << endl;
		for (size_t i = 0; i < LETTERSCOUNT; i++) {
			cout << _codes[i] << " ";
		}
		cout << endl;
	}
	void convertDec2BinAndPrint(int num){
		// convert to binary string (could just cout << the bitset, too)
		std::string bin = std::bitset<CHAR_BIT * sizeof num>(num).to_string();
		// trim leading zeroes
		bin = num ? bin.substr(bin.find('1')) : "0";
		// print
		//std::cout << num << ": [0B" << bin << ']' << '\n';
		//std::cout << num << ": [" << bin << 'b]' << '\n';
	}
	string convertDecToBin(unsigned long int num) {
		int digitsCount = 0, digitsForAlign = 0;
		string codeAlignStr;
		std::string bin = std::bitset<CHAR_BIT * sizeof num>(num).to_string();
		bin = num ? bin.substr(bin.find('1')) : "0";
		digitsCount = bin.size();
		digitsForAlign = log2(LETTERSCOUNT) - (log2(digitsCount) + 1);
		if (digitsForAlign > 0) {
			for (size_t i = 0; i < digitsForAlign; i++) {
				codeAlignStr += "0";
			}
			bin = codeAlignStr + bin;
		}
		return bin;
	}
	string convertDecCodeToBin() {
		string result;
		for (size_t i = 0; i < LETTERSCOUNT; i++) {
			result += convertDecToBin(_codes[i]);
		}
		return result;
	}
	void allLettersCodesCombinationsPrint(int combinationsNo) {
		cout << "List of All Letter's Codes Combinations:" << endl;
		for (size_t j = 0; j < LETTERSCOUNT; j++) {
			//cout << _codes[i] << " ";
			//cout << _allCodesCombinations[combinationsNo][j] << " ";
			cout << _allCodesCombinationsInBin[combinationsNo][j] << " ";
		}
	}
	void allLettersCodesCombinationsGen() {
		//cout << "List of All Letter's Codes Combinations:" << endl;
		/*
		for (size_t i = 0; i < LETTERSCOUNT; i++) {
			for (size_t j = 0; j < LETTERSCOUNT; j++) {
				cout << _letterCodes[i][j] << " ";
			}
			cout << endl;
		}
		*/
		size_t k = 0;
		vector<string> oneCodeCombination;
		do {
			_allCodesCombinations.push_back(_codes);
			for (size_t i = 0; i < LETTERSCOUNT; i++) {
				string binCodeInStr = convertDecToBin(_codes[i]);
				oneCodeCombination.push_back(binCodeInStr);
			}
			_allCodesCombinationsInBin.push_back(oneCodeCombination);
			oneCodeCombination.clear();
			// for debug
			//allLettersCodesCombinationsPrint(k);
			k++;
			//cout << endl;
		} while (std::next_permutation(_codes.begin(), _codes.end() ));

		_combinationsCount = k;
	}
	unsigned long int getCombinationsCount() const {
		return _combinationsCount;
	}
	string getCode(unsigned long int combinationNo, char letter) {
		int letterNumber = 0;
		for (size_t i = 0; i < LETTERSMAXCOUNT; i++) {
			if (_letters[i] == letter) {
				letterNumber = i;
				break;
			}
		}
		if (letterNumber > LETTERSCOUNT-1) {
			letterNumber -= LETTERSCOUNT;
		}
		return _allCodesCombinationsInBin[combinationNo][letterNumber];
	}
	void run() {
		//codes.codesVectorFillup();
		//allCodesPrint();
		lettersCodesInit();
		allLettersCodesCombinationsGen();
	}

} typedef Codes;

int NarayanaNextPerm(int *a, int n)
{
	int i, j, k, t, tmp;
	//Шаг 1
	for (k = n - 2; (k >= 0) && (a[k] >= a[k + 1]); k--);
	//Шаг 2
	if (k == -1)
		return 0;
	for (t = n - 1; a[k] >= a[t]; t--);
	tmp = a[k], a[k] = a[t], a[t] = tmp;
	//Шаг 3
	for (i = k + 1, j = n - 1; i < j; i++, j--)
	{
		tmp = a[i], a[i] = a[j], a[j] = tmp;
	}
	return i;
}

struct WordsLibrary {
	string _words[WORDSCOUNT] = { "армия", "мицар", "мария", "тартур", "рация", "марта", "марат", "тиара", "мирта", "утята", "цитра", "мумия", "тимур", "трата", "римма", "татра", "амати", "артур", "арама" };
	Codes _codes;
	vector<vector<vector<string>>> _wordsBinCodes;
	//unsigned long int _wordsNumbers[WORDSCOUNT];
	vector<unsigned long int> _wordsNumbers;
	unsigned long int _nCombinations = 0;

	void wordsNumberGenerate() {
		for (size_t i = 0; i < WORDSCOUNT; i++) {
			//_wordsNumbers[i] = i;
			_wordsNumbers.push_back(i);
		}
	}
	/*
	string getWords() const{
		return _words;
	}
	*/

	vector<vector<vector<string>>> getWordsBinCodes() const{
		return _wordsBinCodes;
	}

	unsigned long int getCryptoCombinations() {
		return _nCombinations;
	}

	void run() {
		vector<string> _oneWordBinCode;
		vector<vector<string>> _oneWordBinCodingVariant;
		for (size_t k = 0; k < _nCombinations; k++) {
			for (size_t i = 0; i < WORDSCOUNT; i++) {
				for (size_t j = 0; j < _words[i].size(); j++) {
					_oneWordBinCode.push_back(_codes.getCode(k, _words[i][j]));
				}
				_oneWordBinCodingVariant.push_back(_oneWordBinCode);
				_oneWordBinCode.clear();
			}
			_wordsBinCodes.push_back(_oneWordBinCodingVariant);
			_oneWordBinCodingVariant.clear();
		}
	}
	WordsLibrary() {
		_codes.run();
		_nCombinations = _codes.getCombinationsCount();
		run();
		wordsNumberGenerate();
	}
} typedef WordsLib;


struct WordsCombinationSelector {
	vector<string> _wordCombination;
	unsigned long int _wordsCombinationsCount = 0; // 3-element crypto sets numbers
	unsigned long int _cryptoWordsLibVariants;
	string _sourceWordsLibrary[WORDSCOUNT];
	vector<vector<vector<string>>> _sourceWordsBinCodes;
	//vector<int> _wordCombinationInBin;
	//vector<vector<string>> _wordCombinationsForCrackInBinary;
	vector<vector<vector<string>>> _wordCombinationsForCrackInBinary;
	vector<vector<int>> _wordsNumbers;
	vector<string> _setOfWords;

	char* itob(int num, char* buffer, int base)
	{
		if (!num)
			//return '\0';
			return 0;
		char res;
		int i, LEN = strlen(buffer);
		if (num%base > 9) res = (char)(num%base - 10) + 'A';
		else res = (char)(num%base) + '0';

		for (i = LEN; i >= 0; i--)
			buffer[i + 1] = buffer[i];
		buffer[0] = res;

		itob(num / base, buffer, base);
		return buffer;
	}

	string transfer(int number, int numsysBase)
	{
		//cout << "[DEBUG: numsysTransfer()] number = " << number << endl;
		//cout << "[DEBUG: numsysTransfer()] base = " << numsysBase << endl;
		char buffer[NUMSYSBUFFERSIZE] = "";
		itob(number, buffer, numsysBase);
		//cout << buffer << endl;

		//cin.sync(); cin.get();

		return string(buffer);
	}

	int stringToInt(string numInCustomNumSysBase) {
		if (numInCustomNumSysBase != "") {
			return atoi(numInCustomNumSysBase.c_str());
		}
		else
			return 0;
	}

	/*
	bool zeroCheckUp(string str) {
	if (str == "") {
	str = "0";
	return true;
	}
	return false;
	}
	*/

	void init(string wordsLibrary[], vector<vector<vector<string>>>& sourceWordsBinCodes, unsigned long int cryptoVariants) {
		_wordsCombinationsCount = _wordCombination.size();
		_cryptoWordsLibVariants = cryptoVariants;
		for (size_t i = 0; i < WORDSCOUNT; i++) {
			_sourceWordsLibrary[i] = wordsLibrary[i];
		}
		_sourceWordsBinCodes = sourceWordsBinCodes;
	}

	string convertDecToBin(unsigned long int num) {
		int digitsCount = 0, digitsForAlign = 0;
		string codeAlignStr;
		std::string bin = std::bitset<CHAR_BIT * sizeof num>(num).to_string();
		bin = num ? bin.substr(bin.find('1')) : "0";
		digitsCount = bin.size();
		digitsForAlign = log2(LETTERSCOUNT) - (log2(digitsCount) + 1);
		if (digitsForAlign > 0) {
			for (size_t i = 0; i < digitsForAlign; i++) {
				codeAlignStr += "0";
			}
			bin = codeAlignStr + bin;
		}
		return bin;
	}

	/*
	void getWordsNumbersInLibrary() {
		
	}
	*/

	void convertWordsCombinationsToBinary() {
		//int number[WORDSINCRYPTOTEXT];
		int number;
		char curSymbol;
		string resultInBin;
		vector<string> curWordCombinationForCrack;
		vector<vector<string>> curWordsForCrack;
		vector<int> wordsNum;
		for (size_t i = 0; i < _wordsCombinationsCount; i++) {
			for (size_t j = 0; j < WORDSINCRYPTOTEXT; j++) {
				curSymbol = _wordCombination[i][j];
				if (('0' <= curSymbol) && (curSymbol <= '9')) {
					number = curSymbol - '0';
					//resultInBin = convertDecToBin(number);	
					//curWordsCombinationForCrack.push_back(resultInBin);
					wordsNum.push_back(number);
				}
				else {
					number = curSymbol - ('A' - 10);
					wordsNum.push_back(number);
					//curWordsCombinationForCrack.push_back(resultInBin);
				}
				//cout << number;
			}
			_wordsNumbers.push_back(wordsNum);
			wordsNum.clear();
			/*
			for (size_t k = 0; k < _cryptoWordsLibVariants; k++) {
				for (size_t t = 0; t < WORDSINCRYPTOTEXT; t++) {
					curWordCombinationForCrack = _sourceWordsBinCodes[k][number[t]];
					curWordsForCrack.push_back(_sourceWordsBinCodes[k][number[t]]);
				}
				_wordCombinationsForCrackInBinary.push_back(curWordsForCrack);
				curWordsForCrack.clear();
			}
			*/
		}
	}

	void cracking() {
		int wNumbers = _wordsNumbers.size();
		string wordCombination = "";
		//vector<string> setOfWords;
		for (size_t k = 0; k < _wordsCombinationsCount; k++) {
			for (size_t i = 0; i < wNumbers; i++) {
				for (size_t j = 0; j < WORDSINCRYPTOTEXT; j++) {
					for (size_t t = 0; t < _sourceWordsLibrary[_wordsNumbers[i][j]].size(); t++) {
						wordCombination += _sourceWordsBinCodes[k][i][t];
					}
					//_setOfWords.push_back(wordCombination);
				}
				cout << i << endl;
				_setOfWords.push_back(wordCombination);
				wordCombination.clear();
			}
		}
	}

	WordsCombinationSelector(string wordsLibrary[], vector<vector<vector<string>>>& sourceWordsBinCodes, unsigned long int cryptoVariants){
		cout << "======================== SELECT WORDS FOR CRYPTOKEY SEARCH ========================" << endl;

		string numInCustomNumSysBase = "";
		string combinationPart1 = "";
		string combinationPart2 = "";
		string combinationPart3 = "";
		string numInBinary;

		for (size_t i = 0; i < (WORDSCOUNT); i++) {
			combinationPart1 = transfer(i, WORDSCOUNT);
			//zeroCheckUp(combinationPart1);
			if (combinationPart1 == "") {
				combinationPart1 = "0";
			}
			//cout << numInCustomNumSysBase;
			for (size_t j = 0; j < (WORDSCOUNT); j++) {
				combinationPart2 = transfer(j, WORDSCOUNT);
				if (combinationPart2 == "") {
					combinationPart2 += combinationPart1 + "0";
				}
				else {
					combinationPart2 = combinationPart1 + transfer(j, WORDSCOUNT);
				}
				for (size_t k = 0; k < (WORDSCOUNT); k++) {
					combinationPart3 = transfer(k, WORDSCOUNT);
					if (combinationPart3 == "") {
						combinationPart3 += combinationPart2 + "0";
					}
					else {
						combinationPart3 = combinationPart2 + transfer(k, WORDSCOUNT);
					}
					//cout << combinationPart3 << endl;
					_wordCombination.push_back(combinationPart3);
					//cout << numInCustomNumSysBase << endl;
				}
			}
			//numInCustomNumSysBase.clear();
			//int num = stringToInt(numInCustomNumSysBase);
			//numInBinary = transfer(num, 2);
			//cout << numInBinary << endl;
		}
		/*
		unsigned long int combinationsCount = (int)pow(WORDSCOUNT, WORDSINCRYPTOTEXT);
		for (size_t i = 0; i < combinationsCount; i++) {
		numInCustomNumSysBase = transfer(i, WORDSCOUNT);
		cout << numInCustomNumSysBase << endl;
		}
		*/
		init(wordsLibrary, sourceWordsBinCodes, cryptoVariants);
		convertWordsCombinationsToBinary();
		cracking();
	}
	
};

int main()
{
	setlocale(LC_ALL, "Russian");

	time_t startTime, endTime;
	time(&startTime);
	
	//Timer timer("");
	//timer.start();
	WordsLib wordsLib;
	//Codes codes;
	//codes.run();
	//WordsCombinationSelector wordsCombinations(wordsLib._words, wordsLib.getWordsBinCodes());
	WordsCombinationSelector wordsCombinations(wordsLib._words, wordsLib._wordsBinCodes, wordsLib.getCryptoCombinations());

	time(&endTime);
	double seconds = difftime(endTime, startTime);
	cout << "Time (in sec): " << seconds << endl << endl;
	//cout << timer;

	system("pause");
    return 0;
}


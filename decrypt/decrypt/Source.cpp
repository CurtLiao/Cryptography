#include<iostream>
#include<string>
#include<vector>
using namespace std;
//function prototype
std::string lower(std::string t);
string getDigit(int num);
int transNum(string digit);
string exclusive(string input1, string input2);
void Caesar_cipher(std::string message, int keynum);
void Monoalphabetic_cipher(std::string message, const std::string key);
void Playfair_cipher(std::string message, std::string key);   
void Vernam_cipher(string message, string key);               
void Row_transposition(std::string message, vector<int> key);
void Product_cipher(std::string message, vector<int> key);
//main
int main()
{
	bool isContinue = true;
	while (isContinue) {
		vector<int> inputlist;
		std::string inputString = "", inputkeyString = "";
		int i = 0, inputnum = 0, num = 0, typeOfdecrypt = 0;
		std::cout << "(1:Caesar cipher, 2:Monoalphabetic cipher, 3:Playfair cipher, 4:Vernam cipher, 5:Row transposition, 6:Product cipher)" << endl;
		std::cout << "Please input your encrypt type : ";
		std::cin >> typeOfdecrypt;
		switch (typeOfdecrypt)
		{
		case 1:
			std::cout << "Please input cipher :";
			std::cin >> inputString;
			std::cout << "Please input key num :";
			std::cin >> inputnum;
			std::cout << endl;
			std::cout << "You choose Caesar cipher" << endl;
			Caesar_cipher(inputString, inputnum);
			break;
		case 2:
		case 3:
		case 4:
			std::cout << "Please input cipher :";
			std::cin >> inputString;
			std::cout << "Please input key string :";
			std::cin >> inputkeyString;
			std::cout << endl;
			if (typeOfdecrypt == 2) {
				std::cout << "You choose Monoalphabetic cipher" << endl;
				Monoalphabetic_cipher(inputString, inputkeyString);
			}
			else if (typeOfdecrypt == 3) {
				std::cout << "You choose Playfair cipher" << endl;
				Playfair_cipher(inputString, inputkeyString);
			}
			else if (typeOfdecrypt == 4) {
				std::cout << "You choose Vernam cipher" << endl;
				Vernam_cipher(inputString, inputkeyString);
			}
			break;
		case 5:
		case 6:
			std::cout << "Please input cipher :";
			std::cin >> inputString;
			std::cout << "Please input length of key :";
			std::cin >> inputnum;
			std::cout << endl;
			while (i < inputnum) {
				std::cout << "still need to input " << inputnum - i << " number" << endl;
				std::cout << "num = ";
				std::cin >> num;
				inputlist.push_back(num);
				i++;
			}
			if (typeOfdecrypt == 5) {
				std::cout << "You choose Row transposition" << endl;
				Row_transposition(inputString, inputlist);
			}
			else {
				std::cout << "You choose Product cipher" << endl;
				Product_cipher(inputString, inputlist);
			}
			inputlist.clear();
			break;
		default:
			break;
		}
		std::cout << endl << "Continue press 1, exit press 0" << endl;
		std::cin >> isContinue;
	}
	return 0;
}
//function implement
void Caesar_cipher(std::string message, int keynum) {
	char output = ' ';
	std::cout << "Caesar cipher " << " : ";
	std::cout << message << " ---> ";
	for (int i = 0; message[i] != '\0'; i++) {
		output = message[i];
		std::cout << char(tolower(((output - 'Z') - keynum) % 26 + 'Z'));   
	}
	std::cout << std::endl;
	std::cout << std::endl;
}
void Monoalphabetic_cipher(std::string message, const std::string key) {
	char output = ' ';
	const std::string alpha = "zyxwvutsrqponmlkjihgfedcba";
	std::cout << "Monoalphabetic cipher " << " : ";
	std::cout << message << " ---> ";
	for (int i = 0; i < message.size(); i++) {
		for (int j = 0; j < key.size(); j++) {
			if (message[i] == key[j])
				output = alpha[j];
		}
		std::cout << output;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}
void Playfair_cipher(std::string message, std::string key) {
	int index1[2], index2[2];
	std::string keyString = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < key.size(); i++) {             //把 key 拿出來放前面，上下的照著排
		for (int j = 0; j < keyString.size(); j++) {
			if (key[i] == keyString[j])
				keyString.erase(j, 1);
		}
	}
	keyString = key + keyString;
	std::cout << "Playfair cipher " << " : ";
	std::cout << message << " ---> ";
	for (int i = 0; i < message.length(); i += 2) {    //每次只看兩個
		for (int j = 0; j < keyString.length(); j++) {
			if (message[i] == keyString[j]) {
				index1[0] = (j) / 5;
				index1[1] = (j) % 5;
			}
			if (message[i + 1] == keyString[j]) {
				index2[0] = (j) / 5;
				index2[1] = (j) % 5;
			}
		}
		if (index1[0] == index2[0] && index1[1] == index2[1]) {  //同一行同一列，都換成上面那個字母
			index1[0] = (index1[0] + 4) % 5;
			index2[0] = (index2[0] + 4) % 5;
		}
		if (index1[0] != index2[0] && index1[1] != index2[1]) {   //不同行不同列，兩個交換到對方的那行
			std::swap(index1[1], index2[1]);
		}
		if (index1[0] == index2[0] && index1[1] != index2[1]) {   //同列不同行，-1往左移，若是第一個元素則跳回去最後
			index1[1] = ((index1[1] - 1) >= 0) ? (index1[1] - 1) % 5 : (index1[1] + 4) % 5;
			index2[1] = ((index2[1] - 1) >= 0) ? (index2[1] - 1) % 5 : (index2[1] + 4) % 5;
		}
		if (index1[0] != index2[0] && index1[1] == index2[1]) {   //不同列同行，-1往上移，若是第一個元素則跳回去最後
			index1[0] = ((index2[0] - 1) >= 0) ? (index1[0] - 1) % 5 : (index1[0] + 4) % 5;
			index2[0] = ((index2[0] - 1) >= 0) ? (index2[0] - 1) % 5 : (index2[0] + 4) % 5;
		}
		std::cout << char(tolower(keyString[(index1[0] * 5 + index1[1])])) << char(tolower(keyString[(index2[0] * 5 + index2[1])]));
	}
	std::cout << std::endl;
}
void Vernam_cipher(string message, string key) {
	std::cout << endl << "Vernam cipher " << " : ";
	std::cout << message << " ---> ";
	for (int i = 0, k = 0; i < message.size(); i += key.size()) {
		for (int j = 0; j < key.size(); j++) {
			std::string aChar = "", bChar = "",exAns="";
			if (k >= message.size())
				break;
			aChar = getDigit(message[k] - 'A');     //轉成5位元
			bChar = getDigit(key[j] - 'A');         //轉成5位元
			exAns = exclusive(aChar, bChar);		//互斥或
			char ans = char(transNum(exAns)) + 'A'; //轉回去數字，並且用 char 形式 print 出來
			key[j] = ans;
			std::cout << char(tolower(ans));
			k++;
		}
	}
	std::cout << endl;
}
void Row_transposition(std::string message, vector<int> key) {
	std::cout << "Row transposition " << " : ";
	std::cout << message << " ---> ";
	int div = message.size() / key.size();
	int mod = message.size() % key.size();
	vector<int> listCount;
	for (int i = 0; i < mod; i++) {			//把多出一個字母的那行數字放入 vector
		listCount.push_back(key[i]);
	}
	for (int i = 0, count = 0; i < message.size(); i += key.size()) {
		for (int j = 0; j < key.size(); j++) {
			count++;
			if (count > message.size())
				break;
			int index = 0;
			for (int k = 1; k < key[j]; k++) {
				bool countExtra = 0;
				for (int m = 0; m < listCount.size(); m++) {   
					if (k == listCount[m]) {
						index += (div + 1);				//只要現在找的數字在 vector 裡面有，index 就要多加一個
						countExtra = true;				//設為 true，跳出迴圈後判斷 true 就不再加 index
					}
				}
				if (!countExtra)						//false 表示不再 vector 裡面，不用多加一個，照原本的加
					index += div;
			}
			std::cout << (char)(tolower(message[index + (i / key.size())]));
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
}
void Product_cipher(std::string message, vector<int> key) {
	std::cout << "Product cipher " << " : ";
	std::cout << message << " ---> ";
	int temp = 0;
	char tmp = ' ';
	for (int i = 0; i < message.size(); i++) {
		for (int j = 0; j < message.size() - i - 1; j++) {
			if (key[j] > key[j + 1])
			{
				std::swap(key[j], key[j + 1]);    //利用數字去做排列，把對應的 char 也跟著交換
				tmp = message[j];
				message[j] = message[j + 1];
				message[j + 1] = tmp;
			}
		}
	}
	std::cout << lower(message);
	std::cout << std::endl;
	std::cout << std::endl;
}
std::string lower(std::string input) {
	for (int i = 0; i < input.length(); i++) {
		input[i] = tolower(input[i]);
	}
	return input;
}
string getDigit(int count) {
	char digit[5] = { '0','0','0','0','0' };
	for (int i = 4; count > 0; i--) {
		digit[i] = (count % 2) + '0';
		count = count / 2;
	}
	return digit;
}
int transNum(string input) {
	int trans;
	trans = (input[0] - '0') * 16 + (input[1] - '0') * 8 + (input[2] - '0') * 4 + (input[3] - '0') * 2 + (input[4] - '0') * 1;
	return trans;
}
string exclusive(string input1, string input2) {
	char digitChar[5];
	for (int i = 0; i < 5; i++) {
		digitChar[i] = ((input1[i] - '0') ^ (input2[i] - '0')) + '0';
	}
	return digitChar;
}
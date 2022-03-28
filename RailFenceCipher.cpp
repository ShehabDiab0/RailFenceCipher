/*
	 Author: Shehab Diab
	 Program Name: RailFenceCipher.cpp
	 Program Description: Encryption and decryption by converting text into a zigzag from a unique height and adding all rows together
	 and taking a letter from each row in zigzag pattern to decrypt.
	 Last Modification Date: 25/3/2022
	 Purpose: encryption and decryption for texts program
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> zigZagForm(string text, int key);
string railFenceEncryption(string text, int key);
string railFenceDecryption(string cipher, int key);

int main()
{
	int key;
	string text;

	// welcome message
	cout << "Hello User What Would You Like to Do today" << endl;

	while (true)
	{
		// help message
		cout << "Enter\n1 to Encrypt\n2 to Decrypt\n3 to exit\n" << endl;
		string command;
		cin >> command;

		if (command == "1")
		{
			cout << "Enter The Text You Want To encrypt: ";
			cin.ignore();
			getline(cin, text);

			cout << "Enter The Key of the Encryption: ";
			cin >> key;
			cout << "\nEncrypted Text: " << railFenceEncryption(text, key) << "\n\n";

		}
		else if (command == "2")
		{
			cout << "Enter The Text You Want To decrypt: ";
			cin.ignore();
			getline(cin, text);

			cout << "Enter The Key It was Encrypted With: ";
			cin >> key;
			cout << "\nDecrypted Text: " << railFenceDecryption(text, key) << "\n\n";
		}
		else if (command == "3")
		{
			cout << "Thanks For using Our Program :)" << endl;
			break;
		}
		else
		{
			cout << "Please Enter A valid Command" << endl;
		}
	}
}

vector<string> zigZagForm(string text, int key)
{
	vector<string> rows(key);

	// direction to add from rows in the positive and negative direction
	int direction = 1;
	int startRow = 0;

	for (int i = 0; i < text.size(); i++) {
		// add each char to its row
		rows[startRow] += text[i];
		startRow += direction;

		// change direction when its in the first row or last row
		if (startRow == key - 1 || startRow == 0) {
			direction *= -1;
		}
	}

	return rows;
}

string railFenceEncryption(string text, int key)
{
	//removing spaces
	text.erase(remove(text.begin(), text.end(), ' '), text.end());

	string encryptedText = "";

	// zigzag vector of strings
	vector<string> cipherRows = zigZagForm(text, key);

	// adds all rows together in one string
	for (int i = 0; i < cipherRows.size(); i++)
	{
		encryptedText += cipherRows[i];
	}

	return encryptedText;
}

string railFenceDecryption(string cipher, int key)
{
	// removing all spaces
	cipher.erase(remove(cipher.begin(), cipher.end(), ' '), cipher.end());

	int len = cipher.size();

	// chars into zigzag form to know each row length
	// and divide it into nkey of strings
	vector<string> cipherRows = zigZagForm(cipher, key);

	// contains nkey of strings
	// divided parts of the cipher 
	vector<string> decryptedRows(key);

	// divides the cipher into correct string lengths so we can take a char from each string
	for (int i = 0; i < cipherRows.size(); i++)
	{
		string currentRow = cipherRows[i];
		// correct string size for first row in encryption
		int currentRowSize = currentRow.size();

		while (cipher.size() > 0)
		{
			// adds to the rows we want adn erases from cipher text
			decryptedRows[i] += cipher[0];
			cipher.erase(0, 1);

			// if it reached the correct Row size Break
			if (decryptedRows[i].size() == currentRowSize)
			{
				break;
			}
		}
	}

	string decryptedText = "";

	int direction = 1;
	int startRow = 0;

	while (decryptedText.size() < len)
	{
		// take a char from each row like a zig zag
		string currentRow = decryptedRows[startRow];

		if (currentRow != "")
		{
			decryptedText += currentRow[0];
			decryptedRows[startRow].erase(0, 1);
		}

		startRow += direction;

		// change direction
		if (startRow == key - 1 || startRow == 0)
		{
			direction *= -1;
		}
	}

	return decryptedText;
}
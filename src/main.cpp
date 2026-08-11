#include <iostream>
#include <string>
#include <memory>

#include "core/Matrix.h"
#include "core/Alphabet.h"
#include "crypto/Encryptor.h"
#include "crypto/Decryptor.h"
#include "utils/FileUtils.h"

class CryptoApplication {
public:
    CryptoApplication() : matrix(std::make_unique<Matrix>()) {
        initialize();
    }
    
    void run() {
        while (true) {
            showMenu();
            
            int choice = getChoice();
            if (choice == 0) break;
            
            handleChoice(choice);
        }
    }

private:
    std::unique_ptr<Matrix> matrix;
    std::unique_ptr<Alphabet> alphabet;
    std::unique_ptr<Encryptor> encryptor;
    std::unique_ptr<Decryptor> decryptor;
    
    void initialize() {
        const std::string matrixFile = "data/matrix_200x200.txt";
        
        if (!matrix->loadFromFile(matrixFile)) {
            std::cout << "Matrix file not found. Creating new matrix..." << std::endl;
            matrix->createNew();
            matrix->saveToFile(matrixFile);
        }
        
        alphabet = std::make_unique<Alphabet>();
        alphabet->initialize(*matrix);
        
        encryptor = std::make_unique<Encryptor>(*matrix, *alphabet);
        decryptor = std::make_unique<Decryptor>(*matrix, *alphabet);
        
        showSystemInfo();
    }
    
    void showSystemInfo() const {
        std::cout << "\n========================================" << std::endl;
        std::cout << "SYSTEM PARAMETERS:" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Matrix size: " << matrix->getSize() << "x" << matrix->getSize() << std::endl;
        std::cout << "Letters in alphabet: " << alphabet->getLetterCount() << std::endl;
        std::cout << "Routes per letter: " << Alphabet::ROUTES_PER_LETTER << std::endl;
        std::cout << "Total routes: " << alphabet->getTotalRoutes() << std::endl;
        std::cout << "Matrix lifetime: " << Matrix::MAX_LIFETIME << " operations" << std::endl;
        std::cout << "========================================" << std::endl << std::endl;
    }
    
    void showMenu() const {
        std::cout << "\nMENU:" << std::endl;
        std::cout << "1. Encrypt text" << std::endl;
        std::cout << "2. Decrypt text" << std::endl;
        std::cout << "3. Force matrix change" << std::endl;
        std::cout << "4. Show matrix status" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Select action: ";
    }
    
    int getChoice() const {
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        return choice;
    }
    
    void handleChoice(int choice) {
        switch (choice) {
            case 1: encryptText(); break;
            case 2: decryptText(); break;
            case 3: forceMatrixChange(); break;
            case 4: showStatus(); break;
            case 5: 
                std::cout << "Goodbye!" << std::endl;
                exit(0);
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
    
    void encryptText() {
        std::cout << "\nEnter text to encrypt: ";
        std::string text;
        std::getline(std::cin, text);
        
        if (text.empty()) {
            std::cout << "Text cannot be empty!" << std::endl;
            return;
        }
        
        std::cout << "\nEncrypting..." << std::endl;
        std::string encrypted = encryptor->encrypt(text);
        
        std::cout << "\n========================================" << std::endl;
        std::cout << "ENCRYPTED TEXT:" << std::endl;
        
        if (encrypted.length() > 200) {
            std::cout << encrypted.substr(0, 200) << "..." << std::endl;
        } else {
            std::cout << encrypted << std::endl;
        }
        
        std::cout << "========================================" << std::endl;
        std::cout << "Length: " << encrypted.length() << " characters" << std::endl;
        std::cout << "Remaining operations: " << matrix->getRemainingOperations() << std::endl;
        
        if (FileUtils::writeTextFile("encrypted.txt", encrypted)) {
            std::cout << "Saved to file 'encrypted.txt'" << std::endl;
        }
    }
    
    void decryptText() {
        std::cout << "\nEnter text to decrypt (or file path):" << std::endl;
        std::cout << "> ";
        std::string text;
        std::getline(std::cin, text);
        
        // Check if it's a file
        if (text.find('{') == std::string::npos && FileUtils::fileExists(text)) {
            if (FileUtils::readTextFile(text, text)) {
                std::cout << "Loaded from file: " << text.length() << " characters" << std::endl;
            }
        }
        
        if (text.empty()) {
            std::cout << "Text cannot be empty!" << std::endl;
            return;
        }
        
        std::cout << "\nDecrypting..." << std::endl;
        std::string decrypted = decryptor->decrypt(text);
        
        std::cout << "\n========================================" << std::endl;
        std::cout << "DECRYPTED TEXT:" << std::endl;
        std::cout << decrypted << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Remaining operations: " << matrix->getRemainingOperations() << std::endl;
        
        if (FileUtils::writeTextFile("decrypted.txt", decrypted)) {
            std::cout << "Saved to file 'decrypted.txt'" << std::endl;
        }
    }
    
    void forceMatrixChange() {
        std::cout << "\nForcing matrix change!" << std::endl;
        std::cout << "Old messages will become unreadable!" << std::endl;
        std::cout << "Continue? (y/n): ";
        
        char confirm;
        std::cin >> confirm;
        std::cin.ignore();
        
        if (confirm == 'y' || confirm == 'Y') {
            std::string filename = FileUtils::generateTimestampFilename("matrix", "txt");
            filename = "data/" + filename;
            
            matrix->createNew();
            matrix->saveToFile(filename);
            
            // Reinitialize alphabet with new matrix
            alphabet->initialize(*matrix);
            
            std::cout << "Matrix replaced! New lifetime cycle started." << std::endl;
            std::cout << "Saved as: " << filename << std::endl;
        } else {
            std::cout << "Cancelled." << std::endl;
        }
    }
    
    void showStatus() const {
        std::cout << "\n========================================" << std::endl;
        std::cout << "MATRIX STATUS:" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Matrix size: " << matrix->getSize() << "x" << matrix->getSize() << std::endl;
        std::cout << "Total numbers: " << matrix->getData().size() << std::endl;
        std::cout << "Operations used: " << matrix->getOperationCount() 
                  << "/" << Matrix::MAX_LIFETIME << std::endl;
        std::cout << "Remaining operations: " << matrix->getRemainingOperations() << std::endl;
        std::cout << "Routes in memory: " << alphabet->getTotalRoutes() << std::endl;
        
        if (matrix->isExpired()) {
            std::cout << "Matrix lifetime EXPIRED! New matrix required." << std::endl;
        } else {
            std::cout << "Matrix is active and ready for use." << std::endl;
        }
        std::cout << "========================================" << std::endl;
    }
};

int main() {
    try {
        CryptoApplication app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
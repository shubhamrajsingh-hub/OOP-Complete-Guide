#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/**
 * ============================================================================
 * ENCAPSULATION EXAMPLE: Bank Account Management System
 * ============================================================================
 * 
 * Encapsulation is one of the four fundamental OOP concepts that bundles
 * related data (attributes) and methods (functions) together within a class,
 * while hiding internal implementation details from the outside world.
 * 
 * KEY PRINCIPLES:
 * 1. Data Hiding: Private member variables are hidden from direct access
 * 2. Controlled Access: Public getter/setter methods control how data is accessed
 * 3. Protection: Prevent invalid states and maintain data integrity
 * 4. Abstraction: Internal complexity is hidden, only interface is exposed
 * 
 * BENEFITS:
 * - Data Protection: Prevents unauthorized or invalid modifications
 * - Flexibility: Can change internal implementation without affecting external code
 * - Maintainability: Easier to maintain and debug code
 * - Reusability: Encapsulated classes are more reusable
 * ============================================================================
 */

// ============================================================================
// CLASS DEFINITION: BankAccount
// ============================================================================
class BankAccount {
private:
    // PRIVATE DATA MEMBERS - Hidden from direct access
    // These are the sensitive attributes that need protection
    
    string accountNumber;      // Unique identifier for the account
    string accountHolder;      // Name of the account holder
    double balance;            // Current balance in the account
    string accountType;        // Type of account (Savings, Checking, etc.)
    double interestRate;       // Interest rate for the account (for savings accounts)
    
    // Private helper method - for internal use only
    // This method is not exposed to the outside world
    /**
     * Validates if the transaction amount is valid
     * @param amount The amount to validate
     * @return true if amount is valid (positive), false otherwise
     */
    bool isValidAmount(double amount) const {
        return amount > 0;
    }

public:
    // ========================================================================
    // CONSTRUCTOR
    // ========================================================================
    /**
     * Constructor to initialize a BankAccount object
     * 
     * @param accNum The account number
     * @param holder The name of account holder
     * @param initialBalance Initial amount in the account
     * @param type Type of account (Savings/Checking)
     * @param rate Interest rate (default 0.0)
     */
    BankAccount(string accNum, string holder, double initialBalance, 
                string type = "Savings", double rate = 0.0) {
        accountNumber = accNum;
        accountHolder = holder;
        balance = initialBalance;
        accountType = type;
        interestRate = rate;
        
        cout << "✓ Account created successfully!" << endl;
    }

    // ========================================================================
    // PUBLIC GETTER METHODS (Read-Only Access)
    // ========================================================================
    /**
     * Returns the account number
     * This is a CONST method because it doesn't modify object state
     * 
     * @return Account number as a string
     */
    string getAccountNumber() const {
        return accountNumber;
    }

    /**
     * Returns the account holder's name
     * 
     * @return Account holder name as a string
     */
    string getAccountHolder() const {
        return accountHolder;
    }

    /**
     * Returns the current balance
     * NOTE: This returns the actual balance. In a real system,
     * you might want to format this differently or apply fees first.
     * 
     * @return Current balance as a double
     */
    double getBalance() const {
        return balance;
    }

    /**
     * Returns the account type
     * 
     * @return Account type as a string
     */
    string getAccountType() const {
        return accountType;
    }

    /**
     * Returns the interest rate
     * 
     * @return Interest rate as a double
     */
    double getInterestRate() const {
        return interestRate;
    }

    // ========================================================================
    // PUBLIC SETTER METHODS (Controlled Write Access)
    // ========================================================================
    /**
     * Sets the interest rate with validation
     * ENCAPSULATION BENEFIT: Only valid interest rates can be set
     * 
     * @param rate The new interest rate
     * @return true if set successfully, false if invalid
     */
    bool setInterestRate(double rate) {
        // Validation: Interest rate should be reasonable (0-50%)
        if (rate >= 0 && rate <= 50.0) {
            interestRate = rate;
            cout << "✓ Interest rate updated to " << fixed << setprecision(2) 
                 << rate << "%" << endl;
            return true;
        } else {
            cout << "✗ Invalid interest rate! Rate must be between 0 and 50%" << endl;
            return false;
        }
    }

    /**
     * Sets the account holder's name with validation
     * ENCAPSULATION BENEFIT: Ensures account holder name is not empty
     * 
     * @param newHolder The new account holder name
     * @return true if set successfully, false if invalid
     */
    bool setAccountHolder(string newHolder) {
        // Validation: Name should not be empty
        if (!newHolder.empty()) {
            accountHolder = newHolder;
            cout << "✓ Account holder updated to: " << accountHolder << endl;
            return true;
        } else {
            cout << "✗ Invalid name! Account holder name cannot be empty" << endl;
            return false;
        }
    }

    // ========================================================================
    // PUBLIC BUSINESS LOGIC METHODS
    // ========================================================================
    /**
     * Deposits money into the account
     * ENCAPSULATION BENEFIT: Only valid deposits are allowed
     * The internal balance update logic is hidden from the user
     * 
     * @param amount The amount to deposit
     * @return true if deposit successful, false otherwise
     */
    bool deposit(double amount) {
        // Validation: Amount must be positive
        if (!isValidAmount(amount)) {
            cout << "✗ Invalid amount! Deposit amount must be positive" << endl;
            return false;
        }
        
        // Update balance
        balance += amount;
        
        cout << "✓ Deposit Successful!" << endl;
        cout << "  Amount Deposited: $" << fixed << setprecision(2) << amount << endl;
        cout << "  New Balance: $" << balance << endl;
        
        return true;
    }

    /**
     * Withdraws money from the account
     * ENCAPSULATION BENEFIT: Prevents overdraft and invalid withdrawals
     * 
     * @param amount The amount to withdraw
     * @return true if withdrawal successful, false otherwise
     */
    bool withdraw(double amount) {
        // Validation 1: Amount must be positive
        if (!isValidAmount(amount)) {
            cout << "✗ Invalid amount! Withdrawal amount must be positive" << endl;
            return false;
        }
        
        // Validation 2: Prevent overdraft - check if sufficient balance exists
        if (amount > balance) {
            cout << "✗ Insufficient funds!" << endl;
            cout << "  Requested: $" << fixed << setprecision(2) << amount << endl;
            cout << "  Available: $" << balance << endl;
            return false;
        }
        
        // Update balance
        balance -= amount;
        
        cout << "✓ Withdrawal Successful!" << endl;
        cout << "  Amount Withdrawn: $" << fixed << setprecision(2) << amount << endl;
        cout << "  New Balance: $" << balance << endl;
        
        return true;
    }

    /**
     * Transfers money from this account to another account
     * ENCAPSULATION BENEFIT: Encapsulates complex transfer logic
     * 
     * @param toAccount Reference to the destination account
     * @param amount Amount to transfer
     * @return true if transfer successful, false otherwise
     */
    bool transfer(BankAccount &toAccount, double amount) {
        // Validation: Amount must be positive
        if (!isValidAmount(amount)) {
            cout << "✗ Invalid transfer amount! Must be positive" << endl;
            return false;
        }
        
        // Validation: Sufficient balance
        if (amount > balance) {
            cout << "✗ Insufficient funds for transfer!" << endl;
            cout << "  Requested: $" << fixed << setprecision(2) << amount << endl;
            cout << "  Available: $" << balance << endl;
            return false;
        }
        
        // Perform transfer: Withdraw from this account, Deposit to other
        this->balance -= amount;
        toAccount.balance += amount;
        
        cout << "✓ Transfer Successful!" << endl;
        cout << "  From: " << this->accountHolder << " (" << this->accountNumber << ")" << endl;
        cout << "  To: " << toAccount.accountHolder << " (" << toAccount.accountNumber << ")" << endl;
        cout << "  Amount: $" << fixed << setprecision(2) << amount << endl;
        
        return true;
    }

    /**
     * Applies interest to the account balance
     * ENCAPSULATION BENEFIT: Complex calculation is hidden from user
     * 
     * @return The interest amount added
     */
    double applyInterest() {
        double interestAmount = (balance * interestRate) / 100.0;
        balance += interestAmount;
        
        cout << "✓ Interest Applied!" << endl;
        cout << "  Interest Rate: " << fixed << setprecision(2) << interestRate << "%" << endl;
        cout << "  Interest Added: $" << interestAmount << endl;
        cout << "  New Balance: $" << balance << endl;
        
        return interestAmount;
    }

    /**
     * Displays all account information in a formatted manner
     * ENCAPSULATION BENEFIT: Presentation logic is encapsulated
     */
    void displayAccountInfo() const {
        cout << "\n" << string(60, '=') << endl;
        cout << "ACCOUNT INFORMATION" << endl;
        cout << string(60, '=') << endl;
        cout << left;
        cout << setw(25) << "Account Number:" << accountNumber << endl;
        cout << setw(25) << "Account Holder:" << accountHolder << endl;
        cout << setw(25) << "Account Type:" << accountType << endl;
        cout << setw(25) << "Balance:" << "$" << fixed << setprecision(2) << balance << endl;
        cout << setw(25) << "Interest Rate:" << interestRate << "%" << endl;
        cout << string(60, '=') << "\n" << endl;
    }

    // ========================================================================
    // DESTRUCTOR
    // ========================================================================
    /**
     * Destructor called when the object is destroyed
     * Used for cleanup if needed (not necessary here as we don't use dynamic memory)
     */
    ~BankAccount() {
        cout << "Account " << accountNumber << " has been closed." << endl;
    }
};

// ============================================================================
// MAIN FUNCTION - DEMONSTRATION
// ============================================================================
int main() {
    cout << "\n" << string(70, '#') << endl;
    cout << "# C++ ENCAPSULATION EXAMPLE: Bank Account System" << endl;
    cout << string(70, '#') << "\n" << endl;

    // Create bank accounts using the constructor
    // The constructor encapsulates the initialization logic
    cout << "--- Creating Bank Accounts ---\n" << endl;
    BankAccount account1("ACC001", "John Doe", 5000, "Savings", 3.5);
    BankAccount account2("ACC002", "Jane Smith", 10000, "Checking", 1.0);

    // Display account information
    // The displayAccountInfo method encapsulates the presentation logic
    cout << "\n--- Initial Account State ---" << endl;
    account1.displayAccountInfo();
    account2.displayAccountInfo();

    // ========================================================================
    // DEMONSTRATE ENCAPSULATION THROUGH PUBLIC METHODS
    // ========================================================================
    
    cout << "\n--- Testing Encapsulation: Getter Methods ---" << endl;
    cout << "Account 1 Holder: " << account1.getAccountHolder() << endl;
    cout << "Account 1 Balance: $" << fixed << setprecision(2) << account1.getBalance() << endl;
    cout << "Account 1 Interest Rate: " << account1.getInterestRate() << "%\n" << endl;

    // ========================================================================
    // DEMONSTRATE PROTECTED DATA ACCESS
    // ========================================================================
    // NOTE: The following would cause COMPILATION ERROR if uncommented:
    // account1.balance = -5000;  // ERROR: balance is PRIVATE
    // This is the BENEFIT of encapsulation - prevents invalid states!
    
    cout << "--- Testing Encapsulation: Setter Methods with Validation ---\n" << endl;
    
    // Try to set valid interest rate
    cout << "Attempting to set interest rate to 4.5%:" << endl;
    account1.setInterestRate(4.5);
    
    // Try to set invalid interest rate (too high)
    cout << "\nAttempting to set interest rate to 75% (invalid):" << endl;
    account1.setInterestRate(75.0);
    
    // Try to update account holder
    cout << "\nAttempting to update account holder to 'John Smith':" << endl;
    account1.setAccountHolder("John Smith");

    // ========================================================================
    // DEMONSTRATE BUSINESS LOGIC METHODS WITH ENCAPSULATION
    // ========================================================================
    cout << "\n--- Testing Encapsulation: Deposit/Withdraw Methods ---\n" << endl;
    
    // Valid deposit
    cout << "Depositing $2000 to Account 1:" << endl;
    account1.deposit(2000);
    
    // Invalid deposit (negative amount)
    cout << "\nAttempting to deposit -$1000 (invalid):" << endl;
    account1.deposit(-1000);
    
    // Valid withdrawal
    cout << "\nWithdrawing $3000 from Account 1:" << endl;
    account1.withdraw(3000);
    
    // Invalid withdrawal (insufficient funds)
    cout << "\nAttempting to withdraw $100000 (insufficient funds):" << endl;
    account1.withdraw(100000);

    // ========================================================================
    // DEMONSTRATE COMPLEX ENCAPSULATED OPERATIONS
    // ========================================================================
    cout << "\n--- Testing Encapsulation: Interest and Transfers ---\n" << endl;
    
    // Apply interest
    cout << "Applying interest to Account 1 (3.5%):" << endl;
    account1.applyInterest();
    
    // Transfer money between accounts
    cout << "\nTransferring $500 from Account 1 to Account 2:" << endl;
    account1.transfer(account2, 500);
    
    // Try invalid transfer
    cout << "\nAttempting to transfer $50000 (insufficient funds):" << endl;
    account1.transfer(account2, 50000);

    // ========================================================================
    // DISPLAY FINAL ACCOUNT STATE
    // ========================================================================
    cout << "\n--- Final Account State ---" << endl;
    account1.displayAccountInfo();
    account2.displayAccountInfo();

    // ========================================================================
    // SUMMARY OF ENCAPSULATION BENEFITS DEMONSTRATED
    // ========================================================================
    cout << "\n" << string(70, '=') << endl;
    cout << "ENCAPSULATION BENEFITS DEMONSTRATED:" << endl;
    cout << string(70, '=') << endl;
    cout << "1. DATA HIDING: Private attributes (balance, accountNumber, etc.)" << endl;
    cout << "   cannot be accessed directly from outside the class." << endl << endl;
    
    cout << "2. CONTROLLED ACCESS: Public getter/setter methods allow controlled" << endl;
    cout << "   access to private data with validation." << endl << endl;
    
    cout << "3. PROTECTION: Invalid operations are prevented:" << endl;
    cout << "   - Negative amounts cannot be deposited/withdrawn" << endl;
    cout << "   - Overdraft is prevented" << endl;
    cout << "   - Invalid interest rates are rejected" << endl << endl;
    
    cout << "4. ABSTRACTION: Complex business logic is hidden:" << endl;
    cout << "   - User doesn't need to know internal transfer mechanism" << endl;
    cout << "   - Interest calculation logic is encapsulated" << endl;
    cout << "   - Validation logic is hidden from the user" << endl << endl;
    
    cout << "5. FLEXIBILITY: Internal implementation can change without" << endl;
    cout << "   affecting external code that uses the class." << endl;
    cout << string(70, '=') << "\n" << endl;

    return 0;
}

/**
 * ============================================================================
 * OUTPUT EXPLANATION:
 * ============================================================================
 * When you run this program, you'll see:
 * 
 * 1. Account Creation: Two BankAccount objects are created with initial data
 * 2. Account Information Display: All accounts' details are shown
 * 3. Getter Method Tests: Demonstrates reading encapsulated data
 * 4. Setter Method Tests: Shows validation in action
 * 5. Deposit/Withdraw Tests: Demonstrates transaction validation
 * 6. Interest & Transfer Tests: Shows complex encapsulated operations
 * 7. Final State: Updated account information
 * 
 * KEY TAKEAWAY:
 * Encapsulation ensures that the BankAccount class maintains its internal
 * consistency by controlling all access to its data and enforcing business
 * rules through public methods. This makes the code more robust, secure,
 * and maintainable.
 * ============================================================================
 */

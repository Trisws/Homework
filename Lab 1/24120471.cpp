#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <sstream>
using namespace std;

// Chuyển đổi giữa string thành vector<char>
vector<char> stringToVector(const string& s) {
    vector<char> result;
    for (char c : s) {
        result.push_back(c);
    }
    return result;
}

// Chuyển đổi giữa vector<char> thành string
string vectorToString(const vector<char>& v) {
    string result;
    for (char c : v) {
        result += c;
    }
    return result;
}

// Đọc file và lưu vào vector<char>
bool read_file(ifstream& file, vector<char>& data) {
    string line;
    if (getline(file, line)) {
        data.assign(line.begin(), line.end());
        return true;
    }
    return false;
}

int Compare(vector<char>num1, vector<char>num2) {
    // Trị tuyệt đối
    // 1 --> num1 > num2
    // -1 --> num2 > num1

    vector<char> abs1 = (num1[0] == '-') ? vector<char>(num1.begin() + 1, num1.end()) : num1;
    vector<char> abs2 = (num2[0] == '-') ? vector<char>(num2.begin() + 1, num2.end()) : num2;

    int len1 = abs1.size(), len2 = abs2.size();
    if (len1 != len2) return len1 > len2 ? 1 : -1;

    for (int i = 0; i < len1; i++) {
        if (abs1[i] != abs2[i]) return abs1[i] > abs2[i] ? 1 : -1;
    }
    abs1.clear();
    abs2.clear();
    return 0;
}
// Hàm rút gọn số, xóa các số 0 đầu
// Nếu số là 0 thì trả về 0, nếu số âm thì xóa các số 0 sau dấu '-' và trả về số đã rút gọn
void Shorten(vector<char>& num) {
    if (num.empty()) return;

    // Duyệt tới ký tự khác '0' và '-' đầu tiên
    size_t pos = 0;
    if (num[0] == '-') {
        pos = 1;
        while (pos < num.size() && num[pos] == '0') {
            pos++;
        }
        
        // Nếu toàn 0 sau dấu -
        if (pos == num.size()) {
            num = { '0' };
            return;
        }
        
        // Xóa các số 0 sau dấu '-'
        if (pos > 1) {
            num.erase(num.begin() + 1, num.begin() + pos);
        }
    } 
	else {
        while (pos < num.size() && num[pos] == '0') {
            pos++;
        }
        
        // Nếu toàn 0
        if (pos == num.size()) {
            num = { '0' };
            return;
        }
        
        // Xóa các số 0 từ đầu
        if (pos > 0) {
            num.erase(num.begin(), num.begin() + pos);
        }
    }
}

vector<char> Sum(vector<char> num1, vector<char> num2) {
    // Kiểm tra các trường hợp đặc biệt để tránh tràn
    if (num1.size() == 1 && num1[0] == '0') return num2;
    if (num2.size() == 1 && num2[0] == '0') return num1;
    
    //kiểm tra âm dương
    bool n1 = (num1[0] == '-');
    bool n2 = (num2[0] == '-');
    // loại bỏ dấu -
    vector<char> abs1 = (num1[0] == '-') ? vector<char>(num1.begin() + 1, num1.end()) : num1;
    vector<char> abs2 = (num2[0] == '-') ? vector<char>(num2.begin() + 1, num2.end()) : num2;

    int len1 = abs1.size(); int len2 = abs2.size();
    int carry = 0, i = len1 - 1, j = len2 - 1;
    vector<char> result;
    //2 số đều dương
    if (!n1 && !n2) {
        while (j >= 0 || i >= 0 || carry) {
            int digit1 = (i >= 0) ? abs1[i--] - '0' : 0;
            int digit2 = (j >= 0) ? abs2[j--] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            result.push_back((sum % 10) + '0');
            carry = sum / 10;
        }
    }
    //2 số đều âm
    else if (n1 && n2) {
        while (j >= 0 || i >= 0 || carry) {
            int digit1 = (i >= 0) ? abs1[i--] - '0' : 0;
            int digit2 = (j >= 0) ? abs2[j--] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            result.push_back((sum % 10) + '0');
            carry = sum / 10;
        }
        result.push_back('-');
    }
    // 1 âm 1 dương
    else {
        int cmp = Compare(abs1, abs2); // So sánh trị tuyệt đối
        int borrow = 0;
        // 2 số có trị bằng nhau 
        if (cmp == 0) result.push_back('0');
        // |num1| > |num2|
        else if (cmp > 0) {
            vector<char>& larger = abs1;
            vector<char>& smaller = abs2;
            bool isResultNegative = n1;
            
            while (i >= 0) {
                int digit1 = larger[i--] - '0';
                int digit2 = (j >= 0) ? smaller[j--] - '0' : 0;

                int diff = digit1 - digit2 - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                }
                else {
                    borrow = 0;
                }
                result.push_back(diff + '0');
            }
            
            if (isResultNegative) {
                result.push_back('-');
            }
        }
        // |num2| > |num1|
        else {
            vector<char>& larger = abs2;
            vector<char>& smaller = abs1;
            bool isResultNegative = n2;
            
            while (j >= 0) {
                int digit2 = larger[j--] - '0';
                int digit1 = (i >= 0) ? smaller[i--] - '0' : 0;
                int diff = digit2 - digit1 - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                }
                else {
                    borrow = 0;
                }
                result.push_back(diff + '0');
            }
            
            if (isResultNegative) {
                result.push_back('-');
            }
        }
    }
    reverse(result.begin(), result.end());
    Shorten(result);
    return result;
}

vector<char> Subtract(vector<char> num1, vector<char> num2) {
    // Kiểm tra các trường hợp đặc biệt để tránh tràn
    if (num2.size() == 1 && num2[0] == '0') return num1;
    
    // Thay đổi dấu của num2 và sử dụng hàm Sum
    if (num2[0] == '-') {
        vector<char> positiveNum2(num2.begin() + 1, num2.end());
        return Sum(num1, positiveNum2);
    } else {
        vector<char> negativeNum2;
        negativeNum2.push_back('-');
        negativeNum2.insert(negativeNum2.end(), num2.begin(), num2.end());
        return Sum(num1, negativeNum2);
    }
}

vector<char> Multiply(vector<char> num1, vector<char> num2) {
    // Kiểm tra các trường hợp đặc biệt để tránh tràn
    if ((num1.size() == 1 && num1[0] == '0') || (num2.size() == 1 && num2[0] == '0')) {
        return {'0'};
    }
    if (num1.size() == 1 && num1[0] == '1') return num2;
    if (num2.size() == 1 && num2[0] == '1') return num1;
    
    //kiểm tra âm dương
    bool n1 = (num1[0] == '-');
    bool n2 = (num2[0] == '-');
    // loại bỏ dấu -
    vector<char> abs1 = (num1[0] == '-') ? vector<char>(num1.begin() + 1, num1.end()) : num1;
    vector<char> abs2 = (num2[0] == '-') ? vector<char>(num2.begin() + 1, num2.end()) : num2;

    // Sử dụng phương pháp long multiplication đơn giản để tránh vấn đề bộ nhớ
    int len1 = abs1.size();
    int len2 = abs2.size();
    vector<int> result(len1 + len2, 0);
    
    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (abs1[i] - '0') * (abs2[j] - '0');
            int p1 = i + j, p2 = i + j + 1;
            int sum = mul + result[p2];
            
            result[p1] += sum / 10;
            result[p2] = sum % 10;
        }
    }
    
    // Chuyển kết quả thành vector<char>
    vector<char> finalResult;
    bool leadingZeros = true;
    for (int value : result) {
        if (value != 0) leadingZeros = false;
        if (!leadingZeros) finalResult.push_back(value + '0');
    }
    
    if (finalResult.empty()) finalResult.push_back('0');
    
    // Thêm dấu âm nếu cần
    if ((n1 && !n2) || (!n1 && n2)) finalResult.insert(finalResult.begin(), '-');
    
    Shorten(finalResult);
    return finalResult;
}

vector<char> Divide(vector<char> num1, vector<char> num2) {
	//kiểm tra âm dương
	bool n1 = (num1[0] == '-');
	bool n2 = (num2[0] == '-');
	vector<char> dividend = (num1[0] == '-') ? vector<char>(num1.begin() + 1, num1.end()) : num1;
	vector<char> divisor = (num2[0] == '-') ? vector<char>(num2.begin() + 1, num2.end()) : num2;

	// chia cho 0
	if (divisor.size() == 0 || (divisor.size() == 1 && divisor[0] == '0')) {
		throw runtime_error("Cannot divide by zero");
	}

	// dividend = 0
	if (dividend == vector<char>{'0'}) return { '0' };

	// Kiểm tra trường hợp divisor > dividend
	if (Compare(dividend, divisor) < 0) return { '0' };

	vector<char> result;
	vector<char> curr;  // Số hiện tại đang chia
	int idx = 0;
	while (idx < dividend.size()) {
		// Thêm chữ số tiếp theo vào số hiện tại
		curr.push_back(dividend[idx++]);
		Shorten(curr);  // Xóa số 0 đầu nếu có

		// Tìm thương tại vị trí này (Binary search 0-9)
		int digit = 0;
		for (int i = 9; i >= 0; i--) {
			vector<char> prod = Multiply(divisor, { (char)(i + '0') });
			if (Compare(prod, curr) <= 0) {
				digit = i;
				curr = Subtract(curr, prod);
				break;
			}
		}

		result.push_back(digit + '0');
	}
	if ((n1 && !n2) || (!n1 && n2)) result.insert(result.begin(), '-');
	Shorten(result);
	return result;
}
// Hàm kiểm tra độ ưu tiên của toán tử
// Trả về độ ưu tiên của toán tử (1 cho + và -, 2 cho * và /)
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
// Hàm kiểm tra xem ký tự có phải là toán tử không
// Trả về true nếu là toán tử, false nếu không phải
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
// Hàm chuyển đổi biểu thức infix sang postfix
// Sử dụng thuật toán Shunting Yard của Edsger Dijkstra
void Postfix(const string& infix, vector<char>& postfix) {
    // Xóa dữ liệu cũ trong postfix (nếu có)
    postfix.clear();
    
    stack<char> stack;
    bool lastWasDigit = false; // Theo dõi ký tự trước đó có phải là chữ số

    for (size_t i = 0; i < infix.size(); i++) {
        // Trường hợp gặp chữ số hoặc dấu trừ âm
        if (isdigit(infix[i])) {
            while (i < infix.size() && isdigit(infix[i])) {
                postfix.push_back(infix[i++]);
            }
            postfix.push_back(' ');
            lastWasDigit = true;
            i--; // Điều chỉnh chỉ số vì vòng lặp for sẽ tăng i
        }
        // Xử lý dấu trừ âm
        else if (infix[i] == '-' && (i == 0 || infix[i-1] == '(' || isOperator(infix[i-1]))) {
            postfix.push_back('-'); // Đây là dấu trừ âm
            i++;
            while (i < infix.size() && isdigit(infix[i])) {
                postfix.push_back(infix[i++]);
            }
            postfix.push_back(' ');
            lastWasDigit = true;
            i--; // Điều chỉnh chỉ số
        }
        else if (infix[i] == '(') {
            stack.push(infix[i]);
            lastWasDigit = false;
        }
        else if (infix[i] == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix.push_back(stack.top());
                stack.pop();
                postfix.push_back(' ');
            }
            if (!stack.empty()) stack.pop(); // Loại bỏ dấu '('
            lastWasDigit = false;
        }
        else if (isOperator(infix[i])) {
            while (!stack.empty() && stack.top() != '(' && precedence(stack.top()) >= precedence(infix[i])) {
                postfix.push_back(stack.top());
                stack.pop();
                postfix.push_back(' ');
            }
            stack.push(infix[i]);
            lastWasDigit = false;
        }
        // Bỏ qua khoảng trắng
        else if (infix[i] == ' ') {
            continue;
        }
    }

    // Đưa toàn bộ toán tử còn lại trong stack vào postfix
    while (!stack.empty()) {
        postfix.push_back(stack.top());
        stack.pop();
        postfix.push_back(' ');
    }

    // Xóa khoảng trắng cuối cùng nếu có
    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }
}
// Hàm đánh giá biểu thức postfix
// Sử dụng stack để lưu trữ các toán hạng
vector<char> EvaluatePostfix(const vector<char>& postfix) {
    stack<vector<char>> operandStack;
    string currentNumber;
	/*
    // Debug: In ra biểu thức postfix
    cout << "Postfix expression: ";
    for (char c : postfix) cout << c;
    cout << endl;
	*/
    for (size_t i = 0; i < postfix.size(); i++) {
        // Parse numbers (including negative numbers)
        if (isdigit(postfix[i]) || (postfix[i] == '-' && (i + 1 < postfix.size() && isdigit(postfix[i + 1])))) {
            currentNumber = "";
            if (postfix[i] == '-') {
                currentNumber += '-';
                i++;
            }
            while (i < postfix.size() && isdigit(postfix[i])) {
                currentNumber += postfix[i++];
            }
            i--; // Điều chỉnh cho vòng lặp
            
            // Chuyển đổi và đẩy vào stack
            vector<char> num(currentNumber.begin(), currentNumber.end());
            operandStack.push(num);
            /*
            // Debug
            cout << "Pushed number: " << currentNumber << endl;
			*/
        }
        // Bỏ qua khoảng trắng
        else if (postfix[i] == ' ') {
            continue;
        }
        // Xử lý toán tử
        else if (isOperator(postfix[i])) {
            // Kiểm tra có đủ toán hạng không
            if (operandStack.size() < 2) {
                cout << "Error: Not enough operands for operator " << postfix[i] << endl;
                throw runtime_error("Invalid postfix expression: not enough operands");
            }
            
            // Lấy hai toán hạng
            vector<char> b = operandStack.top();
            operandStack.pop();
            vector<char> a = operandStack.top();
            operandStack.pop();
            /*
            // Debug
            cout << "Operation: ";
            for (char c : a) cout << c;
            cout << " " << postfix[i] << " ";
            for (char c : b) cout << c;
            cout << endl;
            */
            // Thực hiện phép toán
            vector<char> result;
            try {
                switch (postfix[i]) {
                    case '+':
                        result = Sum(a, b);
                        break;
                    case '-':
                        result = Subtract(a, b);
                        break;
                    case '*':
                        result = Multiply(a, b);
                        break;
                    case '/':
                        if (b == vector<char>{'0'}) {
                            throw runtime_error("Division by zero");
                        }
                        result = Divide(a, b);
                        break;
                    default:
                        throw runtime_error("Unknown operator: " + string(1, postfix[i]));
                }
                /*
                // Debug
                cout << "Result: ";
                for (char c : result) cout << c;
                cout << endl;
                */

                // Đẩy kết quả vào stack
                operandStack.push(result);
            } catch (const exception& e) {
                cout << "Error in operation: " << e.what() << endl;
                throw;
            }
        }
        else {
            cout << "Unexpected character in postfix: " << postfix[i] << endl;
        }
    }
    
    // Kết quả cuối cùng phải là phần tử duy nhất còn lại trong stack
    if (operandStack.size() != 1) {
        cout << "Error: Invalid postfix expression (stack size = " << operandStack.size() << ")" << endl;
        throw runtime_error("Invalid postfix expression: too many or not enough operands");
    }
    
    return operandStack.top();
}

int main(int argc, char* argv[]) {
    // Kiểm tra số lượng tham số đầu vào
    if (argc != 3) {
        cerr << "Syntax: " << argv[0] << " <file input> <file output>" << endl;
        return 1;
    }

    string inputFileName = argv[1];
    string outputFileName = argv[2];

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Cannot open input file: " << inputFileName << endl;
        return 1;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Unable to open output file: " << outputFileName << endl;
        return 1;
    }
    
    vector<char> data;
    while (read_file(inputFile, data)) {
        try {
            string infix = vectorToString(data);
            vector<char> postfix;
            Postfix(infix, postfix);
            vector<char> result = EvaluatePostfix(postfix);

            cout << "Result: ";
            for (char c : result) cout << c;
            cout << endl;
            
            // Ghi sang file output
            for (char c : result) outputFile << c;
            outputFile << '\n';
            // Xóa data để chuẩn bị cho dòng tiếp theo
            data.clear();
            postfix.clear();
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            outputFile << "ERROR\n";
        }
    }

    inputFile.close();
    outputFile.close();
    return 0;
}

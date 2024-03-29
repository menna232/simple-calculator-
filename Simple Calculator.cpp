#include<iostream>
#include<string>
#include <sstream>
#include <vector>
#define MAX 100000
using namespace std;
string sum(string, string); // this function find the summation of two numbers
bool isSmaller(string str1, string str2);   // this function determine which number is smaller
string findDiff(string str1, string str2); //this function find the subtraction of two numbers
string clearZeros(string Reslut);   //this function getrid of zeros that are in the lef of the first nonzero number
void power(int x, int n);//function to calculate the power of given number
int multiply(int x, int res[], int res_size);//function used fo multiplication in power function
string multiply(string num1, string num2); //FUNCTION FIND MULTIPLICATION OF TWO NUMBERS


int main()
{
    string N1, N2;
    int base, exponent;
    char choice;

    cout << "\t\t\t\tWelcome to basic calculator\t\t\t\t" << endl;
    cout << "(+)Add" << endl;
    cout << "(-)Subtrct" << endl;
    cout << "(*)Multiply" << endl;
    cout << "(^)Power" << endl;
    cout << "Choose an operation:";
    cin >> choice;
    system("CLS");
    switch (choice) {
    case '+':
        cout << "Enter two numbers :" << endl;
        cout << "Number1:";
        cin >> N1;
        cout << "+" << endl;
        cout << "Number2:";
        cin >> N2;
        cout << "Result= " << sum(N1, N2) << endl;
        system("pause");
        system("CLS");
        main();
        break;
    case '-':
        cout << "Enter two numbers :" << endl;
        cout << "Number1:";
        cin >> N1;
        cout << "-" << endl;
        cout << "Number2:";
        cin >> N2;

        cout << "Result= " << findDiff(N1, N2) << endl;
        system("pause");
        system("CLS");
        main();
        break;
    case '*':
        cout << "Enter two numbers: " << endl;
        cout << "Number1: ";
        cin >> N1;
        cout << "*" << endl;
        cout << "Number2: ";
        cin >> N2;
        cout << "Result= ";
        if ((N1.at(0) == '-' || N2.at(0) == '-') &&
            (N1.at(0) != '-' || N2.at(0) != '-') && (N1.at(0) != '0' && N2.at(0) != '0'))
            cout << "-";
        if (N1.at(0) == '-')
            N1 = N1.substr(1);

        if (N2.at(0) == '-')
            N2 = N2.substr(1);
        cout << multiply(N1, N2) << endl;
        system("pause");
        system("CLS");
        main();
        break;
    case '^':
        cout << "Enter two numbers: " << endl;
        cout << "The base: ";
        cin >> base;
        cout << "^" << endl;
        cout << "The exponent: ";
        cin >> exponent;
        cout << "Result= ";
        power(base, exponent);
        cout << endl;
        system("pause");
        system("CLS");
        main();
        break;
    default:
        cout << "unidentified operator" << endl;
        system("pause");
        system("cls");
        main();

    }
    system("pause");
    return 0;
}


string sum(string num1, string num2) {
    //if just one number is negative
    string R = "";
    char num1Sign = '+', num2Sign = '+';
    if (num1[0] == '-' && num2[0] != '-' || num2[0] == '-' && num1[0] != '-') {
        if (num1[0] == '-') {
            num1 = num1.substr(1);
            num1Sign = '-';
        }
        else {
            num2 = num2.substr(1);
            num2Sign = '-';
        }
        R = findDiff(num1, num2);
        if (R[0] == '-')
            R = R.substr(1);
        reverse(R.begin(), R.end());

        //if one number is negative the the summation will be nagative if the biggest number is negative
        if (isSmaller(num1, num2) && num2Sign == '-')
            R += '-';



        else if (!isSmaller(num1, num2) && num1Sign == '-')
            R += '-';




        reverse(R.begin(), R.end());
        return clearZeros(R);

    }

    char signCheck = '+';        //if the two enterd numbers are positive this variable will equal to +
    if (num1[0] == '-' && num2[0] == '-')
    {
        /*if the two enterd numbers are negative this variable will equal to -
         and we will remove the negative sign from both numbers
         and we will add it in the end of summtion as you see in line 113 */
        signCheck = '-';
        num1 = num1.substr(1);
        num2 = num2.substr(1);
    }



    int carry = 0, n1, n2, size1, size2, result, i1, i2;


    size1 = num1.length();
    size2 = num2.length();
    for (i1 = size1 - 1, i2 = size2 - 1; i1 >= 0 || i2 >= 0; i1--, i2--) {
        if (i1 >= 0) {
            n1 = num1[i1] - '0';
        }

        else {
            n1 = 0;
        }

        if (i2 >= 0) {

            n2 = num2[i2] - '0';
        }
        else {
            n2 = 0;
        }
        result = n1 + n2 + carry;
        //in case the outout of summation is one digit
        if (result < 10) {
            R += to_string(result);
            carry = 0;
        }
        //in case the output of summation is two digits so subtract the number from ten to get first digit
        else {
            result -= 10;
            carry = 1;
            R += to_string(result);

        }

    }//end for loop

    if (carry == 1)
        R += "1";

    if (signCheck == '-')
        R += '-';


    reverse(R.begin(), R.end());
    return clearZeros(R);
}



bool isSmaller(string str1, string str2)
{

    // Calculate lengths of both string
    int n1 = str1.length(), n2 = str2.length();

    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;

    for (int i = 0; i < n1; i++) {
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
    }
    return false;
}

string findDiff(string str1, string str2)
{
    // Take an empty string for storing result
    string str = "";
    char ResultSign = '+';

    //if just the first number is negative
    if (str1[0] == '-' && str2[0] != '-') {
        reverse(str2.begin(), str2.end());
        str2.push_back('-');
        reverse(str2.begin(), str2.end());
        return clearZeros(str = sum(str1, str2));
    }

    // if just the second number is negative
    if (str2[0] == '-' && str1[0] != '-') {
        str2 = str2.substr(1);
        return clearZeros(str = sum(str1, str2));

    }

    // if both number is negative
    if (str1[0] == '-' && str2[0] == '-') {
        str2 = str2.substr(1);
        return clearZeros(str = sum(str1, str2));
    }

    //if both number is positive but the first number is smaller tha  the second number
    if (str2[0] != '-' && str1[0] != '-' && isSmaller(str1, str2))
        ResultSign = '-';



    // Before proceeding further, make sure str1
    // is not smaller
    if (isSmaller(str1, str2))
        swap(str1, str2);


    // Calculate lengths of both string
    int n1 = str1.length(), n2 = str2.length();
    int diff = n1 - n2;

    // Initially take carry zero
    int carry = 0;// Traverse from end of both strings
    for (int i = n2 - 1; i >= 0; i--) {
        // Do school mathematics, compute difference of
        // current digits and carry
        int sub = ((str1[i + diff] - '0') - (str2[i] - '0')
            - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    // subtract remaining digits of str1[]
    for (int i = n1 - n2 - 1; i >= 0; i--) {
        if (str1[i] == '0' && carry) {
            str.push_back('9');
            continue;
        }
        int sub = ((str1[i] - '0') - carry);
        if (i > 0 || sub > 0) // remove preceding 0's
            str.push_back(sub + '0');
        carry = 0;
    }





    // reverse resultant string
    reverse(str.begin(), str.end());
    string solution = clearZeros(str);

    //if both number is positive but the first number is smaller tha  the second number
    if (ResultSign == '-') {
        reverse(solution.begin(), solution.end());
        solution += '-';
        reverse(solution.begin(), solution.end());
    }

    return solution;

}


//in case of negative number will take (-) as C.F then return it to sum then cout it with answer
string clearZeros(string Result) {
    int catchIndex = 0;
    for (int i = 0; i < Result.length(); i++)
    {
        if (Result[i] != '0')
        {
            catchIndex = i;
            break;
        }

    }
    Result = Result.substr(catchIndex);
    return Result;
}





int multiply(int x, int res[], int res_size) {
    int carry = 0;
    for (int i = 0; i < res_size; i++) {
        int prod = res[i] * x + carry;


        res[i] = prod % 10;


        carry = prod / 10;
    }
    while (carry) {
        res[res_size] = carry % 10;
        carry = carry / 10;
        res_size++;
    }
    return res_size;
}


void power(int x, int n)
{
    bool negative = false;
    if (x < 0 && n % 2 != 0)
    {
        negative = true;
        x *= -1;
    }
    // IF THE NUMBER IS NEGATIVE AND THE POWER IS NOT EVEN , WILL RETURN (-) TO THE RESULT
    if (x == 0)
    {
        cout << "0";
        return;
    }
    // IF BASE IS ZERO THEN IT WILL ALWAYS OUTPUT ZERO

    if (n == 0) {
        cout << "1";
        return;
    }
    //this case for exponent equals to zero will output one
    int res[MAX];
    int res_size = 0;
    int temp = x;
    //to store the input numbers into the array
    while (temp != 0)
    {
        res[res_size++] = temp % 10;

        temp = temp / 10;
    }
    //the for loop is to multiplication according to number of n ex: x^n=x*x*x*x*x*x
    for (int i = 2; i <= n; i++)
        res_size = multiply(x, res, res_size);

    cout << x << "^" << n << " = ";
    if (negative == true)
        cout << "-";
    for (int i = res_size - 1; i >= 0; i--)
        cout << res[i];
}


string multiply(string num1, string num2)
{
    string solution;
    int nLength1 = num1.size();
    int nLength2 = num2.size();
    int result[1000] = { 0 };
    for (int i = nLength1 - 1; i >= 0; i--)
    {
        for (int j = nLength2 - 1; j >= 0; j--)
        {
            result[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
            //store the multiplication of two nums after changing them to int from chars and add them to the carry
            result[i + j] += result[i + j + 1] / 10;
            //sum the number to the carry , divide it to get first digit and store it to the next smaller index
            result[i + j + 1] %= 10;
            //store the last digit
        }

    }
    int x = 0;
    bool zerofound = true;
    for (int z = 0; z < nLength1 + nLength2; z++)
    {
        if (result[z] != 0)
        {
            x = z;
            zerofound = false;
            //check for non zeros and test if the whole array contain zeros to change bool to false
            break;
        }
    }
    if (zerofound == true)
    {
        solution.push_back(0 + '0');

        return solution;

        //if all the array is zeros output one zero only
    }
    else
    {
        //if theres non zero nums in the array(we uses this function with summation and subraction);
        for (int z = x; z < nLength1 + nLength2; z++)
        {
            solution.push_back(result[z] + '0');
            //store the int to vector of string after changing the int to char
        }

        return solution;
    }
}

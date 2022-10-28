#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif


//unsigned Add_Checksum 
unsigned int add_checksum( unsigned int n ) {    

    //Initialize Variables
    int array[8]; 
    int checksum_value{0};
    int second_n{0};

    //Storing n value into second variable to keep original number
    second_n = n;

    //Run if digits in number are valid (any positive number that is less than or equal to 8 digits)
    if(n <= 99999999){

        //Store the number into an array with 7 numbers (0-6 places)
        for (int i{7}; i >= 0; --i){
            array[i] = n%10;
            n /= 10;
        }
        
        //For loop to multiply the second digit from the right by 2
        for(int k{7}; k >= 1; k = k - 2){
            array[k] *= 2;

            //If any value in array is greater than 9, then add the 1s and 10s place 
            if(array[k] > 9){
                array[k] = (array[k]%10) + 1;
            } 
        }

        //For loop to add all values in array to a int variable called checksum value 
        for(int l{0}; l <=7; ++l){
            checksum_value += array[l];
        }

        //Math to find the correct checksum value from the 8 digit number
        checksum_value *= 9;
        checksum_value %= 10;

        //Code adds checksum value to the end of initial number and storing into variable called second_n
        second_n = (second_n*10) + checksum_value;

    //If n value is larger than 8 digits, than output UNIT_MAX to show error
    } else if(n > 99999999){
        return UINT_MAX;
    }
    
    //Return the n value with checksum added to the end
    return second_n;
}

//Void Add_Checksum 
void add_checksum ( unsigned int array [], std::size_t capacity ){

    //Set int variable a to capacity to create max limit for the for loop
    int a = capacity;

    //For loop to run checksum function for every value in the array
    for(int i{0}; i < a; ++i){
        array[i] = add_checksum(array[i]);
    }
}

//Verify_Checksum
bool verify_checksum( unsigned int n ){

    int a = add_checksum(n/10);

    if((n <= 999999999) && (n == a) ){
        return true;
    } else{
        return false;
    }
}

//Unsigned Remove checksum
unsigned int remove_checksum( unsigned int n ){

    if(!verify_checksum(n)){
        return UINT_MAX;
    }
    if(n > 999999999){
        return UINT_MAX;
    }
    return n/10;
}

//Void Remove checksum
void remove_checksum( unsigned int array[], std::size_t capacity ){

    //Set int variable b to capacity to create max limit for the for loop
    //For loop to run remove checksum function for every value in the array
    for(int i{0}; i < capacity; ++i){
        array[i] = remove_checksum(array[i]);
    }
}


#ifndef MARMOSET_TESTING
int main() {

//Add_Checksum 
    unsigned int value_to_protect{12345678};
    unsigned int protected_value = add_checksum(value_to_protect);
    std::cout << "The value " << value_to_protect
    << " with the checksum added is " << protected_value
    << "." << std::endl;

//Verify Checksum
    if (verify_checksum(protected_value))
    {
    std::cout << "The checksum is valid." << std::endl;
    } else {
    std::cout << "The checksum is invalid." << std::endl;
    }

//Void Add_Checksum
    const std::size_t QTY_VALUES {6};
     unsigned int value_series[QTY_VALUES] {12345678, 85743748, 985747232, 48593, 98765676, 57947324};
    add_checksum(value_series, QTY_VALUES);
    std::cout << "Series with checksums added: ";
    for (std::size_t series_index {0};
    series_index < QTY_VALUES; series_index++)
    {
    std::cout << value_series[series_index] << " ";
    }
    std::cout << std::endl;

//Remove_Checksum
    unsigned int value_to_protect2{202240120};
        unsigned int protected_value2 = remove_checksum(value_to_protect2);
        std::cout << "The value " << value_to_protect2
        << " with the checksum removed is " << protected_value2
        << "." << std::endl;

//Void Remove_Checksum
    const std::size_t QTY_VALUES2 {6};
    unsigned int value_series2[QTY_VALUES2] {202011224, 202099131, 202240120, 29292, 29392099, 123456782};
    remove_checksum(value_series2, QTY_VALUES2);
    std::cout << "Series with checksums removed: ";
    for (std::size_t series_index2 {0};
    series_index2 < QTY_VALUES2; series_index2++)
    {
    std::cout << value_series2[series_index2] << " ";
    }
std::cout << std::endl;

return 0;
}
#endif

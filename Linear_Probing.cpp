#include <iostream>
#include <string>
using namespace std;
#define size 10

string hash_table[size]; // table
int num = 0;  // number of item in the table

void init()
{   // initialize the array with empty
    for(int i = 0; i < size; i++)
        hash_table[i] = "empty";
}

int hash_fun(string email)
{   // hash the email
    // convert it to integer value
    int value = 0;
    int index = 0;
    for(int i =0 ; i < email.length(); i++){
        value += (int)email[i];
    }
    return ( value * 7) % 10;
}

void insert(string email)
{   // get the index of the email
    int index = hash_fun(email);
    if(num < size){ // table not completed
        if(hash_table[index] == "empty" || hash_table[index]== "delete"){
            // the index maybe empty or maybe deleted
            hash_table[index] = email; // put the email
            num = num + 1; // increment the num of item
        }else{ // index not available
            int loop = ( index + 1) % size; // next index
            while(loop != index){ // loop utile git the same place of index
                // the next index is deleted or empty
                if(hash_table[loop] == "empty" || hash_table[loop]== "delete"){
                    hash_table[loop] = email;
                    num = num + 1;
                    loop = index; // find index go break rules
                }else{
                    loop = ( loop + 1) % size;
                }
            }//end of while
        }
    }
    else{ //  table full size
        cout<<"\n table is completed \n";
    }
}
int find_index(string email)
{ //check if index exist
    int index = hash_fun(email);
    if(num == 0){ // no items (-1)
        return -1;
    }else{ // have item
        if(hash_table[index] == email){
            return index; // index exist and was the first
        }else{ // index maybe in any index
            int loop = (index + 1) % size; // increment index
            while(loop != index && hash_table[loop] != "empty"){
                if(hash_table[loop] == email){ // index found
                    return loop;
                }
                else{
                    loop = loop + 1;
                }
            }
        }
    }
    return -1; // index not found
}
void delete_email(string email)
{   // the num until delete
    int old_num = num;
    int index = hash_fun(email);
    if(num == 0){ // table is empty
        cout<<"table is empty\n";
    }   // find the email in first index
    else if(hash_table[index] == email){
        hash_table[index] = "delete"; // delete
        num = num - 1; // decrease num of items
        cout << "Email "<<email <<" was deleted"<<endl;
    }
    else{ //search if exist
        int index = find_index(email);
        if(index >= 0){ // if exist
            hash_table[index] = "delete"; // delete
            cout << "Email "<<email <<" was deleted"<<endl;
        }
        else{ // not exist
            cout<<"Email " << email << " was not found\n";
        }
    }
}

void find_email(string email){
    if(num == 0){
        cout<<"there is No item in table";
    }
    else{
        int index = find_index(email);
        if( index > 0){
            cout<< "Email " << hash_table[index] << " was found\n";
        }
        else{
            cout << "Email " << email << " was not found \n";
        }
    }
}
void update()
{
    if(num == 0){
        cout<<"no item in table to update";
    }
    else if(num == size){ // table is full
        cout<<"table is full Enter the email you wanna to update\n";
        string old_email;
        cin>> old_email; // email you wanna to update
        int index = find_index(old_email);
        if(index > 0){ // email wanna to update is found
            cout<< "Enter the new email \n";
            string new_email;
            cin >> new_email;
            // table is full then update directly
            hash_table[index] = new_email;
        }
        else{
            cout<<"email not found";
        }
    }
    else{ //table have items but not full
        cout<<"Enter the email you wanna to update\n";
        string old_email;
        cin>> old_email;
        int index = find_index(old_email); // find the index
        if(index > 0){ // email wanna to update is found
            cout<< "Enter the new email \n";
            string new_email;
            cin >> new_email;
            // index with old_email = index with new
            // then add
            if(index == hash_fun(new_email))
                hash_table[index] = new_email;
            else{ // index not equal
                    // then delete old add new
                delete_email(hash_table[index]);
                insert(new_email);
            }
        }
    }
}

void print()
{
    cout << "\n";
    for (int i = 0; i < size; i++)
    {
        cout<< hash_table[i] << " , ";
    }
}

int main()
{
    init();
    //cout<<hashfun("a");
    //cout<<hashfun("k");
    insert("a");
    insert("k");
    insert("u");
    insert("d");
    insert("s");
    insert("Aa");
    insert("Aas");
    //insert("asd");
    //insert("Aas");
    insert("asd");
    print();
    delete_email("s");
    delete_email("Aas");
    delete_email("mom");
    print();
    find_email("mohamed");

    return 0;
}

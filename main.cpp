#include <iostream>
#include <sstream>

class HashTable 
{
    public:
    // data organisation 
        
        struct Entry
        {
            std::string  Data;
            std:: string Status="never used";
        };
        static const int Size=26;

    public:
    // Default constructor is enough
        HashTable()=default;

    // Add entry when starts with character 'A'
        void Add( const std:: string& entryString )
        {
            
            bool exists=Find(entryString);
            if(!exists)
            {
                int insertIndex=GetInsertIndex(entryString);
                m_Entries[insertIndex].Data=entryString;
                m_Entries[insertIndex].Status="occupied";

             }
        }
    // Delete entry when stats with character 'D'
        void Delete(const std:: string& entryString)
        {
            int index;
            bool exists=Find(entryString, &index);
            if(exists)
                m_Entries[index].Status="tombstone";
        }

    //Print result 

        void print() const
        {
            for (int i=0; i< Size; ++i)
            {
                //std:: cout<<m_Entries[i].Data<< " ("<< m_Entries[i].Status<<")"<< std::endl;
                if(m_Entries[i].Status == "occupied")
                    std:: cout<<m_Entries[i].Data<< " ";
            }
            std::cout << std::endl; 
        }

        void printNoExtraSpace() const
        {
            bool first=true;

            for (int i=0; i< Size; ++i)
            {
                
                if(m_Entries[i].Status == "occupied")
                {   
                    if(!first)
                        std::cout<< " ";

                    std:: cout<<m_Entries[i].Data;
                    first=false;
                }
            }
            std::cout << std::endl; 
        }

        void printDebugMode() const
        {
            for (int i=0; i< Size; ++i)
            {
                std:: cout<<m_Entries[i].Data<< " ("<< m_Entries[i].Status<<")"<< std::endl;
                
            }
        }

    private:
    
    
    // hash function: Get the index of the last character in the entryName
        int GetIndex(const std:: string& entryString) const
        {
            // ASCII code'a' =97  and 'z'=122
            // should just extract the numeric value od character 'a' to map the hashtable from 0 to 25
            
            return entryString.back()- 'a';
        }

        bool Find(const std:: string& entryString, int* outIndex=nullptr) const
        {
            int index=GetIndex(entryString);
            
            while(true)
            {
                if(m_Entries[index].Data== entryString)
                    {
                        if(outIndex)
                            *outIndex=index;
                        return true;
                    }
                if(m_Entries[index].Status== "never used")
                    return false;
                index=(index+1)% Size;
            }
            return false;
        }


        int GetInsertIndex(const std:: string& entryString) const
        {
            int index=GetIndex(entryString);

            while(true)
            {
                if(m_Entries[index].Status== "never used" || m_Entries[index].Status == "tombstone")
                    return index;

                index= (index +1) % Size;
            
            }
            return -1;
        }


    // private member variable
    private:
        Entry m_Entries[Size];


  
};



int main() {

    //Test example
    // input:  Aapple Aorange Dapple Astrawberry
    // output: Orange strawberry

    std:: string input;
    getline(std::cin, input);

    HashTable hashTable;

    std::stringstream ss(input);
    while (ss.good())
    {
        std::string token;

        ss >> token;
        
        // We do not need the first character which is an indication of add or delete
        // Thus subtract form index 1;
        std::string entryString= token.substr(1);

        // if the first character is an A 
        // run a command to add 
        if(token[0]=='A')
        {

            hashTable.Add(entryString);


        }

        // if the first character is an A 
        // run a command to delete
        else if(token[0]=='D')
        {
            hashTable.Delete(entryString);

        } 
    }

    hashTable.printDebugMode();
}
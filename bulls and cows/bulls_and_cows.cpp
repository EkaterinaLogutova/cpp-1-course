#include <iostream>
#include <ctime>
#include <random>
#include <array>
#include <vector>
#include <algorithm>

using value = std::array<int, 4>;

constexpr unsigned int len{4};
constexpr int finish{1000};

bool work_with_player(unsigned int bulls, unsigned int cows)

{
    bool game_continue{true};

    if(bulls==len)
    {
        std::cout<<"Congratulations! You win!"<<std::endl;
        game_continue=false;
    }
    else
    {
        std::cout<<"bulls: "<<bulls<<"\n"<<"cows:"<<cows<<std::endl;
    }
    return game_continue;
}

value generate()
{
    srand(time(NULL));

    value result;

    bool repeat {false};
    unsigned int count=0;
    while (count<len)
    {
        result[count]=rand()%10;
        for(unsigned int j=0; j<count; ++j)
        {
            if (result[count]==result[j])
            {
                repeat=true;
                break;
            }
        }
        if (!repeat)
        {
            ++count;
        }
        repeat=false;
    }
    return result;
}
value generate_2(std::vector<int> bad)
{
    srand(time(NULL));

    value result;

    bool repeat{false};
    unsigned int count=0;
    while (count<len)
    {
        result[count]=rand()%10;
        if ((std::find(bad.begin(), bad.end(), result[count])!=bad.end()) && !(bad.empty()))
        {
            repeat= true;
        }

        for(unsigned int j=0; j<count; ++j)
        {
            if (result[count]==result[j])
            {
                repeat = true;
                break;
            }
        }
        if (!repeat)
        {
            ++count;
        }
        repeat=false;
    }
    return result;
}

value symbols(int player_number)
{
    value symb;
    for(int i=len-1; i>=0; --i)
        {
            int symbol{player_number%10};
            symb[i]=symbol;
            player_number=(player_number-symbol)/10;
        }
    return symb;
}
std::vector<int> bc_player(std::vector<int> bad, value result)
{
    std::cout<<"\nHow bulls and cows i have? (bulls cows)"<<std::endl;
    int bulls{};
    int cows{};
    std::cin>>bulls>>cows;
    if (cows==0 && bulls==0)
    {
        for(unsigned int i=0; i<len; ++i)
        {
            bad.push_back(result[i]);
        } 
    }
    if(bulls==len)
    {
        std::cout<<"Hah, i win"<<std::endl;
        bad.push_back(finish);
    }
    return bad;
}

bool bulls_and_cows(value symb, value result)
{
    int bulls=0;
    int cows=0;

    for(unsigned int j=0; j<len; ++j)
    {
        if(symb[j]==result[j])
        {
            ++bulls;
        }
    }
    for(unsigned j=0; j<len; ++j)
    {
        for(unsigned int k=0; k<len; ++k)
        {
            if(symb[j]==result[k] && j!=k)
            {
                ++cows;
            }
        }
    }
    
    return work_with_player(bulls, cows);
}

int main()
{

    constexpr unsigned int max_attemps{10};

    std::cout<<"Try to guess the number, you have "<<max_attemps<<" attemps"<<std::endl;

    value result{generate()};
    bool game_continue{true};
    std::vector<int> bad{};

    for(int i=0; i<max_attemps; ++i)
    {
        std::cout<<"Write your number:";
        int player_number {};
        std::cin>>player_number;
        value symb{symbols(player_number)};

        game_continue=bulls_and_cows(symb, result);
        if(!game_continue)
        {
            break;
        }
        std::cout<<"So, that's my turn"<<std::endl;
        value prediction{generate_2(bad)};
        std::cout<<"I think your number is: ";
        for(unsigned int j=0; j<len; ++j)
        {
            std::cout<<prediction[j];
        }
        bad=bc_player(bad, prediction);
        if (!bad.empty() && bad.back()==finish)
        {
            break;
        }

    }
    if(game_continue)
    {
        std::cout<<"So sad, you've lost\n";
        std::cout<<"The target was ";
        for(unsigned int j=0; j<len; ++j)
        {
            std::cout<<result[j];
        }
    }
}
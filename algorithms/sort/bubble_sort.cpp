#include<iostream>
#include<vector>

void bubble_sort(std::vector<int> &a)
{
    for (size_t i = 0; i < a.size()-1; i++)
    {
        for (size_t j = 0; j < a.size()-1-i; j++)
        {
            if (a[j]>a[j+1])
            {
                std::swap(a[j],a[j+1]);
            }
        }
    }
}
void bubble_sort(std::vector<double> &a)
{
    for (size_t i = 0; i < a.size()-1; i++)
    {
        for (size_t j = 0; j < a.size()-1-i; j++)
        {
            if (a[j]>a[j+1])
            {
                std::swap(a[j],a[j+1]);
            }
        }
    }
}
void select_sort(std::vector<int> &a)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        size_t minIndex = i;
        for (size_t j = i+1; j < a.size(); j++)
        {
            if(a[i]>a[j])
            {
                minIndex = j;
            }
        }
        if(minIndex != i)
        {
            std::swap(a[minIndex],a[i]);
        }

        
    }
}
void select_sort(std::vector<double> &a)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        size_t minIndex = i;
        for (size_t j = i+1; j < a.size(); j++)
        {
            if(a[i]>a[j])
            {
                minIndex = j;
            }
        }
        if(minIndex != i)
        {
            std::swap(a[minIndex],a[i]);
        }

        
    }
}

int main()
{
    std::vector<int> a = {2,4,52,1,55,7};
    std::vector<double> b = {2.1,4.5,52.2,1.1,55.2,7.0};

    // bubble_sort(a);
    // for (auto i : a)
    // {
    //     std::cout<<i<<" "<<std::endl;
    // }

    // bubble_sort(a);
    // for (auto i : a)
    // {
    //     std::cout<<i<<" "<<std::endl;
    // }

    select_sort(b);
    for (auto i : b)
    {
        std::cout<<i<<" "<<std::endl;
    }
    return 0;
}

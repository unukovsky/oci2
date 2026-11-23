#include <iostream>
#include <vector>
#include <windows.h>

struct ThreadData
 {
    std::vector<int>* arr;
    int minVal = 0;
    int maxVal = 0;
    int averageVal = 0;
};

DWORD WINAPI MinMaxThread(LPVOID lpParam)
{
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    const std::vector<int>& arr = *(data->arr);
    int minElem = arr[0];
    int maxElem = arr[0];
    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr[i] < minElem)
        {
            minElem = arr[i];
        }
        Sleep(7);

        if (arr[i] > maxElem)
        {
            maxElem = arr[i];
        }
        Sleep(7);
    }
    data->minVal = minElem;
    data->maxVal = maxElem;
    std::cout << "Min el: " << minElem << std::endl;
    std::cout << "Max el: " << maxElem << std::endl;
    return 0;
}

DWORD WINAPI AverageThread(LPVOID lpParam)
{
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    const std::vector<int>& arr = *(data->arr);
    long long sum = 0;
    for (size_t i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
        Sleep(12);
    }
    data->averageVal=sum / arr.size();
    std::cout << "Av val: " << data->averageVal << std::endl;
    return 0;
}

int main()
{
    int n;
    std::cout << "size: ";
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    ThreadData data;
    data.arr = &arr;
    HANDLE hMinMax = CreateThread(
        NULL,
        0,
        MinMaxThread,
        &data,
        0,
        NULL
    );
    WaitForSingleObject(hMinMax, INFINITE);

    HANDLE hAverage = CreateThread(
        NULL,
        0,
        AverageThread,
        &data,
        0,
        NULL
    );
    WaitForSingleObject(hAverage, INFINITE);

    for (int i = 0; i < n; ++i)
    {
        if (arr[i] == data.minVal || arr[i] == data.maxVal)
        {
            arr[i] = data.averageVal;
        }
    }

    std::cout << "ans: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    return 0;
}

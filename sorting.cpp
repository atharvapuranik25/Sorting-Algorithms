//This is a program containing various sorting algorithms.
//It also gives the time taken to for executing each sorting algotrithm

#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std::chrono;
using namespace std;

//Class containing methods for all the sorting algorithms
class Sorting
{
public:
    
    //Home function calls the banner and the choice function which displays a menu
    void home()
    {
        system("CLS");
        banner();
        int result;
        result = choice();
        action(result);
    }

    //Banner for the program
    void banner()
    {
        cout << "##########################" << endl;
        cout << "    Sorting Algorithms" << endl;
        cout << "##########################" << endl;
    }

    //Menu for asking the user for a choice
    int choice()
    {
        int x;
        cout << "\nChoose: " << endl;
        cout << "1. Selection Sort" << endl;
        cout << "2. Bubble Sort" << endl;
        cout << "3. Insertion Sort" << endl;
        cout << "4. Quick Sort" << endl;
        cout << "5. Merge Sort" << endl;
        cout << "6. Exit" << endl;
        cout << "\nEnter you choice: ";
        cin >> x;
        return x;
    }

    //Calling the sorting algorithm based on user input
    void action(int res)
    {
        if (res == 1)
        {
            selectionSort();
            home();
        }
        else if (res == 2)
        {
            bubbleSort();
            home();
        }
        else if (res == 3)
        {
            insertionSort();
            home();
        }
        else if (res == 4)
        {
            vector<int> data = read();

            cout << "Quick Sort\n"
                 << endl;

            // Start time
            auto start = high_resolution_clock::now();

            data = quickSort(data, 0, data.size() - 1);

            // Stop time
            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(stop - start);

            cout << "Time taken for execution: " << duration.count() << endl;

            sleep(5);

            rewriteFile(data);

            sleep(5);

            home();
        }
        else if (res == 5)
        {
            vector<int> data = read();

            cout << "Merge Sort\n"
                 << endl;

            // Start time
            auto start = high_resolution_clock::now();

            data = mergeSort(data);

            // Stop time
            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(stop - start);

            cout << "Time taken for execution: " << duration.count() << endl;

            sleep(5);

            rewriteFile(data);

            sleep(5);

            home();
        }
        else if (res == 6)
        {
            exit(0);
        }
        else
        {
            cout << "\nInvalid Input" << endl;
            cout << "Redirecting back to home screen..." << endl;
            sleep(2);
            home();
        }
    }

    //Initially writing data to file 
    void writeFile()
    {
        fstream file;
        int write_val;
        int i = 0;

        file.open("data.txt", ios::trunc | ios::out | ios::in);

        while (i < 10000)
        {
            write_val = rand();
            file << write_val << endl;
            i++;
        }

        file.close();
    }

    //Rewriting data to file before executing the sorting algorithm, just in case the data is already sorted
    void rewriteFile(vector<int> data)
    {
        fstream file;
        int write_val;

        file.open("data.txt", ios::trunc | ios::out | ios::in);

        for (int i = 0; i < 10000; i++)
        {
            write_val = data[i];
            file << write_val << endl;
        }

        file.close();
    }

    //Read data from the file and add it to a vector
    vector<int> read()
    {
        writeFile();
        vector<int> data;
        fstream file;
        int read_val;

        file.open("data.txt", ios::out | ios::in);

        file.seekg(0, ios::beg);

        while (!file.eof())
        {
            file >> read_val;
            data.push_back(read_val);
        }

        file.close();

        return data;
    }

    //Selection sort algorithm
    void selectionSort()
    {
        cout << "Selection Sort\n"
             << endl;
        vector<int> data = read();
        int size = data.size();

        // Start time
        auto start = high_resolution_clock::now();

        for (int j = 0; j < size - 1; j++)
        {
            int min = j;

            for (int i = j + 1; i < size; i++)
            {
                if (data.at(min) > data.at(i))
                {
                    min = i;
                }
            }

            if (min != j)
            {
                swap(data.at(j), data.at(min));
            }
        }

        // Stop time
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Time taken for execution: " << duration.count() << endl;

        sleep(5);

        rewriteFile(data);

        sleep(5);
    }

    //Bubble sort algorithm
    void bubbleSort()
    {
        cout << "Bubble Sort\n"
             << endl;
        vector<int> data = read();
        int size = data.size();

        // Start time
        auto start = high_resolution_clock::now();

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size - 1; j++)
            {
                if (data[j] > data[j + 1])
                {
                    swap(data.at(j), data.at(j + 1));
                }
            }
        }

        // Stop time
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Time taken for execution: " << duration.count() << endl;

        sleep(5);

        rewriteFile(data);

        sleep(5);
    }

    //Insertion sort algorithm
    void insertionSort()
    {
        cout << "Insertion Sort\n"
             << endl;
        vector<int> data = read();
        int size = data.size();

        // Start time
        auto start = high_resolution_clock::now();

        for (int i = 0; i < size; i++)
        {
            int j = i;
            int temp = data[i];

            while (j > 0 && temp < data[j - 1])
            {
                data[j] = data[j - 1];
                j--;
            }

            data[j] = temp;
        }

        // Stop time
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Time taken for execution: " << duration.count() << endl;

        sleep(5);

        rewriteFile(data);

        sleep(5);
    }

    //Quick sort algorithm
    vector<int> quickSort(vector<int> &data, int left, int right)
    {
        if (left < right)
        {
            int pivot = divide(data, left, right);
            quickSort(data, left, pivot - 1);
            quickSort(data, pivot, right);
        }
        return data;
    }

    //Divide the vector received from the quickSort function around the pivot element
    int divide(vector<int> &data, int left, int right)
    {
        int pivot = left + (right - left) / 2;
        int pivotValue = data[pivot];
        int temp;

        while (left <= right)
        {
            while (data[left] < pivotValue)
            {
                left++;
            }

            while (data[right] > pivotValue)
            {
                right--;
            }

            if (left <= right)
            {
                temp = data[left];
                data[left] = data[right];
                data[right] = temp;
                left++;
                right--;
            }
        }

        return left;
    }

    //Merge sort algorithm
    vector<int> mergeSort(vector<int> data)
    {
        if (data.size() <= 1)
            return data;

        vector<int> left, right, result;
        int middle = (data.size() + 1) / 2;

        for (int i = 0; i < middle; i++)
        {
            left.push_back(data[i]);
        }

        for (int i = middle; i < data.size(); i++)
        {
            right.push_back(data[i]);
        }

        left = mergeSort(left);
        right = mergeSort(right);
        result = merge(left, right);

        return result;
    }

    //Merge the left and right vector received from the mergeSort function
    vector<int> merge(vector<int> left, vector<int> right)
    {
        vector<int> result;
        while (left.size() > 0 || right.size() > 0)
        {
            if (left.size() > 0 && right.size() > 0)
            {
                if (left.front() <= right.front())
                {
                    result.push_back(left.front());
                    left.erase(left.begin());
                }
                else
                {
                    result.push_back(right.front());
                    right.erase(right.begin());
                }
            }
            else if (left.size() > 0)
            {
                for (int i = 0; i < left.size(); i++)
                    result.push_back(left[i]);
                break;
            }
            else if (right.size() > 0)
            {
                for (int i = 0; i < right.size(); i++)
                    result.push_back(right[i]);
                break;
            }
        }
        return result;
    }
};

int main()
{
    Sorting sort;
    sort.home();
}
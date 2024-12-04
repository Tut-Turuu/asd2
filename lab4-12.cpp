#include <iostream>
#include <functional>
#include <cstring>
#include <cmath>
#include <fstream>

/*Comb sort*/
void comb_sort(int* arr, int size) {
    int step = size - 1;
    float factor = 1.25;

    while (step >= 1) {
        for (int i = 0; i + step < size; ++i) 
            if (arr[i+ step] < arr[i]) 
                std::swap(arr[i+step], arr[i]);
        
        step /= factor;
    }
}

void insertion_sort(int* arr, int size) {

    int curr;
    int j;
    for (int i = 0; i < size; ++i) {
        curr = arr[i];
        j = i - 1;
        while (j > -1 && curr < arr[j]) {
            arr[j + 1] = arr[j];
            --j; 
        } 
        arr[j+1] = curr;
    }
}

/*Util*/
int* min_ptr(int* arr, int size) {
    int mn = 0x7fffffff;
    int* mn_ptr = nullptr;
    for (int i = 0; i < size; ++i) {
        if (arr[i] < mn) {
            mn = arr[i];
            mn_ptr = arr + i;
        }
    }
    return mn_ptr;
}

void selection_sort(int* arr, int size) {

    for (int i = 0; i < size; ++i) {
        std::swap(arr[i], *(min_ptr(arr + i, size - i)));
    }
}

void shell_sort(int* arr, int size) {
    int step = size / 2;
    int curr;
    int k;
    while (step != 0) {
        for (int i = 0; i < step; ++i) {
            for (int j = i + step; j < size; j += step) {
                curr = arr[j];
                k = j - step;
                while (k > -1 && curr < arr[k]) {
                    arr[k + step] = arr[k];
                    k -= step;
                }
                arr[k + step] = curr;
            }
        }
        step /= 2;
    }
}



void radix_sort(int* arr, int size) {
	int maxNegative = 0;
	for (int i = 0; i < size; i++) {
		maxNegative = std::min(maxNegative, arr[i]);
	}
	for (int i = 0; i < size; i++) {
		arr[i] -= maxNegative;
	}

	int mx = -2147483647 - 1;
	for (int i = 0; i < size; i++) {
		mx = std::max(mx, arr[i]);
	}
	int maxNumberLength = 0;
	while (mx > 0) {
		maxNumberLength++;
		mx /= 10;
	}

	for (int i = 0; i < maxNumberLength; i++) {
		std::vector<int> digits[10];
		for (int j = 0; j < size; j++) {
			int digit = (arr[j] % int(std::pow(10, i + 1))) / std::pow(10, i);
			digits[digit].push_back(arr[j]);
		}
		int index = 0;
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < digits[j].size(); k++) {
				arr[index] = digits[j][k];
				index++;
			}
		}
	}

	for (int i = 0; i < size; i++) {
		arr[i] += maxNegative;
	}
}


void heapify(int* arr, int size, int i) {
	int largest = i;

	int left = 2 * i + 1, right = 2 * i + 2;

	if (left < size && arr[left] > arr[largest]) {
		largest = left;
	}

	if (right < size && arr[right] > arr[largest]) {
		largest = right;
	}

	if (largest != i) {
		std::swap(arr[i], arr[largest]);
		heapify(arr, size, largest);
	}
}

void heap_sort(int* arr, int size) {

	for (int i = size / 2 - 1; i >= 0; i--) {
		heapify(arr, size, i);
	}

	for (int i = size - 1; i >= 0; i--) {
		std::swap(arr[0], arr[i]);

		heapify(arr, size, 0);
	}
}

void merge_sort(int* arr, int size) {
    if (size > 1) {
        int leftSize = size / 2;
        int rightSize = size - leftSize;

        merge_sort(arr, leftSize);
        merge_sort(arr + leftSize, rightSize);
 
        int lInd = 0, rInd = leftSize, ind = 0;
        int* tmpArr = new int[size];

        while (lInd < leftSize || rInd < size) {
            if (arr[lInd] < arr[rInd]) {
                tmpArr[ind] = arr[lInd];
                ind++;
                lInd++;
            }
            else {
                tmpArr[ind] = arr[rInd];
                ind++;
                rInd++;
            }

            if (lInd == leftSize) {
                for (; rInd < size; rInd++) {
                    tmpArr[ind] = arr[rInd];
                    ind++;
                }
                break;
            }
            if (rInd == size) {
                for (; lInd < leftSize; lInd++) {
                    tmpArr[ind] = arr[lInd];
                    ind++;
                }
                break;
            }
        }

        for (int i = 0; i < size; i++) {
            arr[i] = tmpArr[i];
        }

        delete[] tmpArr;
    }
}

void quick_sort(int* arr, int l, int r) {
	if (r - l >= 1) {
		int pivot = arr[l];
		int smallerInd = l - 1;
		int biggerInd = r + 1;

		for (int i = l; i < biggerInd; i++) {
			while (i > smallerInd && i < biggerInd && arr[i] != pivot) {
				if (arr[i] < pivot) {
					smallerInd++;
					std::swap(arr[i], arr[smallerInd]);
				}
				if (arr[i] > pivot) {
					biggerInd--;
					std::swap(arr[i], arr[biggerInd]);
				}
			}
		}

		quick_sort(arr, l, smallerInd);
		quick_sort(arr, biggerInd, r);
	}
}


void read_input_data(int chunkLen) {
	std::ifstream in("input.txt", std::ios::in);

	std::ofstream outA("tempA.txt", std::ios::out);
	std::ofstream outB("tempB.txt", std::ios::out);

	char currentOut = 'A';
	int* arr = new int[chunkLen];

	while (!in.eof()) {
		int i = 0;

		while (!in.eof() && i < chunkLen) {
			in >> arr[i];
			i++;
		}
		
		if (!in.eof()) {
			quick_sort(arr, 0, i - 1);

			if (currentOut == 'A') {
				int n = i;

				for (i = 0; i < n; i++) {
					outA << arr[i] << std::endl;
				}

				currentOut = 'B';
			}
			else if (currentOut == 'B') {
				int n = i;

				for (i = 0; i < n; i++) {
					outB << arr[i] << std::endl;
				}

				currentOut = 'A';
			}
		}
		else {
			quick_sort(arr, 0, i - 2);

			if (currentOut == 'A') {
				int n = i - 1;

				for (i = 0; i < n; i++) {
					outA << arr[i] << std::endl;
				}

				currentOut = 'B';
			}
			else if (currentOut == 'B') {
				int n = i - 1;

				for (i = 0; i < n; i++) {
					outB << arr[i] << std::endl;
				}

				currentOut = 'A';
			}
		}
	}
	delete[] arr;
}
/* Gets data from input.txt */
void external_polyphase_sort(int chunk_len) {
	int size = chunk_len;
	char input1 = 'A';
	char input2 = 'B';
	char current_output = 'C';

	int out_cnt1 = -1, out_cnt2 = -1;

	while (out_cnt1 != 0 && out_cnt2 != 0) {
		out_cnt1 = 0;
		out_cnt2 = 0;

		std::ifstream in1;
		std::ifstream in2;

		std::ofstream out1;
		std::ofstream out2;
		if (input1 == 'A') {
			in1.open("tempA.txt", std::ios::in);
			in2.open("tempB.txt", std::ios::in);

			out1.open("tempC.txt", std::ios::out);
			out2.open("tempD.txt", std::ios::out);
		}
		if (input1 == 'C') {
			in1.open("tempC.txt", std::ios::in);
			in2.open("tempD.txt", std::ios::in);

			out1.open("tempA.txt", std::ios::out);
			out2.open("tempB.txt", std::ios::out);
		}

		while (!in1.eof() && !in2.eof()) {
			int already_read1 = 0, already_read2 = 0;
			int value1, value2;
			bool used1 = true, used2 = true;

			while ((already_read1 < size && !in1.eof()) || !used1 || (already_read2 < size && !in2.eof()) || !used2) {
				if (already_read1 < size && !in1.eof() && used1) {
					in1 >> value1;
					if (!in1.eof()) {
						used1 = false;
						++already_read1;
					}
				}
				if (already_read2 < size && !in2.eof() && used2) {
					in2 >> value2;
					if (!in2.eof()) {
						used2 = false;
						++already_read2;
					}
				}

				if (used1 == false && used2 == false) {
					if (value1 <= value2) {
						if (current_output == 'A' || current_output == 'C') {
							out1 << value1 << std::endl;
							used1 = true;
							++out_cnt1;
						}
						else {
							out2 << value1 << std::endl;
							used1 = true;
							++out_cnt2;
						}
					}
					else {
						if (current_output == 'A' || current_output == 'C') {
							out1 << value2 << std::endl;
							used2 = true;
							++out_cnt1;
						}
						else {
							out2 << value2 << std::endl;
							used2 = true;
							++out_cnt2;
						}
					}
				}
				else if(used1 == false) {
					if (current_output == 'A' || current_output == 'C') {
						out1 << value1 << std::endl;
						used1 = true;
						out_cnt1++;
					}
					else {
						out2 << value1 << std::endl;
						used1 = true;
						++out_cnt2;
					}
				}
				else if (used2 == false) {
					if (current_output == 'A' || current_output == 'C') {
						out1 << value2 << std::endl;
						used2 = true;
						++out_cnt1;
					}
					else {
						out2 << value2 << std::endl;
						used2 = true;
						++out_cnt2;
					}
				}
			}

			if (current_output == 'A') {
				current_output = 'B';
			}
			else if (current_output == 'B') {
				current_output = 'A';
			}
			else if (current_output == 'C') {
				current_output = 'D';
			}
			else if (current_output == 'D') {
				current_output = 'C';
			}
		}

		size *= 2;
		if (input1 == 'A') {
			input1 = 'C';
			input2 = 'D';
			current_output = 'A';
		}
		else if(input1 == 'C'){
			input1 = 'A';
			input2 = 'B';
			current_output = 'C';
		}
	}

	std::ifstream in;
	std::ofstream out("output.txt", std::ios::out);

	if (current_output == 'C') {
		in.open("tempA.txt", std::ios::in);
	}
	else {
		in.open("tempC.txt", std::ios::in);
	}

	while (!in.eof()) {
		int value;
		in >> value;
		if (!in.eof()) {
			out << value << std::endl;
		}
	}
}

int main(int argc, char** argv) {
    std::function<void(int*, int)> sort_alg;
    
    if (!strcmp(argv[1], "--help")) {
        std::cout << "Usage: " << argv[0] << " [OPTION]\nOPTIONS:\n\tcomb\n\tinsertion\n\tselection\n\tshell\n";
        return 0;
    }
    else if (!strcmp(argv[1], "comb")) {
        sort_alg = comb_sort;
    }
    else if (!strcmp(argv[1], "insertion")) {
        sort_alg = insertion_sort;
    }
    else if (!strcmp(argv[1], "selection")) {
        sort_alg = selection_sort;
    }
    else if (!strcmp(argv[1], "shell")) {
        sort_alg = shell_sort;
    }
    else if (!strcmp(argv[1], "radix")) {
        sort_alg = radix_sort;
    }
    else if (!strcmp(argv[1], "heap")) {
        sort_alg = heap_sort;
    }
    else if (!strcmp(argv[1], "merge")) {
        sort_alg = merge_sort;
    }
    else if (!strcmp(argv[1], "quick")) {
        sort_alg = quick_sort;
    }
    else if (!strcmp(argv[1], "external_polyphase")) {
        sort_alg = external_polyphase_sort;
    }
    else {
        std::cout << "Invalid option, type " << argv[0] << " --help for more information.";
        return 0;
    }

    int arr[100];
    int size;
    

    std::cout << "Введите длину массива чисел и сам массив: ";
    std::cin >> size;

    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    sort_alg(arr, size);

    std::cout << "Отсортированный массив:\n";
    for (int i = 0 ; i < size; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

    
    
}
#include <fstream>
#include <iostream>
#include <cstring> // for strcmp
using namespace std;

const int char_buffer = 1000;
char buffer[char_buffer];
const int max_lines = 100;
char *lines[max_lines];

int main() 
{
  int buffer_idx = 0;
  int line_count = 0;

  char ch;

  // Open file
  ifstream file("input.txt");
  if (!file.is_open()) 
  {
    cout << "Error: Could not open input.txt" << endl;
    return 1;
  }

  // First line starts at buffer[0]
  lines[line_count++] = &buffer[0];

  // Read file into buffer
  while (buffer_idx < (char_buffer - 1) && file.get(ch)) 
  {
    if (ch == '\n') 
    {
      buffer[buffer_idx++] = '\0';

      if (line_count < max_lines) 
      {
        lines[line_count++] = &buffer[buffer_idx];
      }
    }
    else
    {
      buffer[buffer_idx++] = ch;
    }
  }
  buffer[buffer_idx] = '\0'; // Null-terminate last line

  file.close();

  // Print lines in original order
  cout << "Original lines:\n";
  for (int i = 0; i < line_count; ++i) 
  {
    cout << lines[i] << endl;
  }

  // Sort lines using pointer swapping (simple bubble sort)
  for (int i = 0; i < line_count - 1; ++i) 
  {
    for (int j = i + 1; j < line_count; ++j) 
    {
      if (strcmp(lines[i], lines[j]) > 0) 
      {
        char *temp = lines[i];
        lines[i] = lines[j];
        lines[j] = temp;
      }
    }
  }

  // Print sorted lines
  cout << "\nSorted lines:\n";
  for (int i = 0; i < line_count; ++i) 
  {
    cout << lines[i] << endl;
  }

  return 0;
}

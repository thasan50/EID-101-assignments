#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main () {
    string line;
    vector<double> time1;
    vector<double> speedLimit;
    vector<double> time2;
    vector<double> speed;
    int tickets = 0;

    ifstream file("speedlimit.csv");
    if (!file.is_open()) {
        cout << "File could not be opened" << endl;
        return 1;
    }

    getline(file, line);
    while (getline(file, line)) {
        size_t comma_pos = line.find(',');
            string time = line.substr(0, comma_pos);
            string limit = line.substr(comma_pos + 1);
            time1.push_back(stod(time));
            speedLimit.push_back(stod(limit));
    }
    file.close();
   
    //Inserted the values from the speedlimit csv into two vectors

    ifstream file2("driving_data.csv");
    if (!file2.is_open()) {
        cout << "File could not be opened" << endl;
        return 1;
    }

    getline(file2, line);
    while (getline(file2, line)) {
        size_t comma_pos = line.find(',');
            string time = line.substr(0, comma_pos);
            string limit = line.substr(comma_pos + 1);
            time2.push_back(stod(time));
            speed.push_back(stod(limit));
    }
    file2.close();
    // for (size_t a = 0; a < time2.size(); a++) {
    //     cout << time2[a] << " " << speed[a] << endl;
    // }
    //Inserted the values from the driving_data csv into two vectors
    //Now time to compare data
    size_t counter = 0;
    double last_time = 0;
    for (size_t i = 0; i < time2.size(); i++) {
        //Basically, for each sample of driving data, I want to find the corresponding speed limit. Then we can decide whether to issue a penalty.
            //This should be a while loop
        while (time1.size() > counter + 1 && time2[i] > time1[counter+1]) {
            counter++;
        }
        if (time1.size() <= counter+1) {
            //compare time from driving data with very last speed limit
            counter--;
        }
        if (time2[i] < time1[counter+1]) {
            if (speed[i] > 3.0 + speedLimit[counter] && speedLimit[counter] > 30.0) {
                if (time2[i] - last_time > 5.0) {
                    tickets++;
                    last_time = time2[i];
                }
            }
            else if (speed[i] > 3.0 + speedLimit[counter] && speedLimit[counter] <= 30.0) {
                if (time2[i] - last_time > 5.0) {
                    tickets++;
                    last_time = time2[i];
                }
            }
        }
            
    }
    cout << tickets << endl;
    return 0;
}
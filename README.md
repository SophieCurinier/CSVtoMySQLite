# CSVtoMySQLite

## About the project
Sensors record at regular intervals, all their activity data of the last 24 hours in the form of csv. So we have folders full of csv files where we can have duplicate lines.
We want the data to be entered at regular intervals in a sqlite database. In the database, there should be no duplicates and the data should be clean. 
Once the data is retrieved, the csv files must be deleted.

## Getting start
### Prerequisites
- CMake version 3.25.1
- vcpkg version 2023-04-07
- gcc version 12

### Installation
1. Clone the repo
```sh
   git clone https://github.com/SophieCurinier/CSVtoMySQLite.git
```
2. Compile
3. Launch
```sh
    main --database databasePath --directory directoryPath [--logfile logfilePath]
```

## License
Distributed under the MIT License. See `LICENSE.txt` for more information.

## Contact
Curinier Sophie - sophie.curinier@gmail.com

Projet link : [https://github.com/SophieCurinier/CSVtoMySQLite](https://github.com/SophieCurinier/CSVtoMySQLite)

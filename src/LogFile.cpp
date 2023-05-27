#pragma once
#include <iostream>
#include <fstream>

using namespace std ;

class LogFile 
{
    ofstream m_logFile ;
    string m_filePath ;
    static LogFile *s_instance;

    LogFile(int v = 0)
    {
        m_filePath = "";
    }

    public :
        static LogFile *instance(){
            if (!s_instance){
                s_instance = new LogFile;
            }
            return s_instance;
        };

        void set_filePath(string filePath){
            m_filePath = filePath;
        }

        void log(string message){
            m_logFile.open(m_filePath, ios::app);
            if (m_logFile.is_open()){
                m_logFile << message << endl;
                cout << message << endl;
            }
            m_logFile.close();
        }

        void logError(string message){
            m_logFile.open(m_filePath, ios::app);
            if (m_logFile.is_open()){
                m_logFile << message << endl;
                cerr << message << endl;
            }
            m_logFile.close();
        }
};

LogFile *LogFile::s_instance = 0;

//
//  main.cpp
//  CopyConstructor
//
//  Created by Ethan Shang on 5/4/17.
//  Copyright © 2017 Ethan Shang. All rights reserved.
//

#include <iostream>
#include <cmath>

using namespace std;

class Vector3D
{
    double x, y, z;
public:
    Vector3D(double x1, double y1, double z1){
        x = x1;
        y = y1;
        z = z1;
    }
    
    Vector3D operator+(Vector3D rhs) //a + b
    {
        return Vector3D(x + rhs.x,
                        y + rhs.y,
                        z + rhs.z);
    }
    
    Vector3D operator-(Vector3D rhs) //a - b
    {
        return Vector3D(x - rhs.x,
                        y - rhs.y,
                        z - rhs.z);
    }
    
    Vector3D operator*(double scalar) //a * s
    {
        return Vector3D(x * scalar,
                        y * scalar,
                        z * scalar);
    }
    
    Vector3D operator-() //-a
    {
        return Vector3D(operator*(-1));
    }
    
    double operator*(Vector3D rhs) //a * b
    {
        return (x*rhs.x +
                y*rhs.y +
                z*rhs.z);
    }
    
    Vector3D operator^(Vector3D rhs) //a ^ b
    {
        
        return Vector3D(y*rhs.z -  z * rhs.y, z*rhs.x - x*rhs.z, x * rhs.y - y*rhs.x);
        
    }
    
    double operator~() //~a
    {
        return sqrt(x*x + y*y + z*z);
    }
    
    friend ostream& operator<<(ostream &out, Vector3D &rhs)
    {
        return out << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
    }
};

int main()
{
    Vector3D a(1, 2, 3);
    Vector3D b(3,2,1);
    Vector3D c = (a+b);
    Vector3D d = (a-b);
    // a.operator+(b) --- that's what's happening under the hood
    Vector3D e = (-a);
    Vector3D f  = (a*4);
    double  g = (a*b);
    Vector3D h = (a^b);
    
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << endl << "Addition: " << c << endl;
    cout << endl << "Subtraction: " << d << endl;
    cout << endl << "Negatition: " << e << endl;
    cout << endl << "Scalar (4): "  <<  f << endl;
    cout << endl << "Dot Product: " << g << endl;
    cout << endl << "Cross Product: " << h << endl;
    return 0;
}


//#include <iostream>
//using namespace std;
//const double DEFAULT_SCORE = 0.0;
//class StudentTestScores{
//private:
//    string studentName;
//    double * testScores;
//    /// points to array of test scores
//    int numTestScore;public:
//    StudentTestScores(string name, int numScores)
//    {
//        studentName = name;
//        numTestScore = numScores;
//        testScores = new double[numTestScore];
//        for (int i = 0; i < numTestScore; i++)
//        {
//            testScores[i] = DEFAULT_SCORE;
//        }
//    }
//    ~StudentTestScores()
//    {
//        delete [] testScores;
//    }
//    void setName(string name)
//    {
//        studentName = name;
//        return;
//           }
//    string getName()
//    {
//        return studentName;
//    }
//    void setTestScore(double score, int index)
//    {
//        testScores[index] = score;
//        return;
//    }
//    double getTestScore(int index)
//    {
//        return testScores[index];
//    }
//    void dispalyNameNAllScores()
//    {
//        cout << getName() << endl;
//        for (int i = 0; i < numTestScore; i++)
//        {            cout << getTestScore(i) << "  ";
//        }
//    }
//    /// Copy constructor
//    /// Enter your code here
//};
//    int main(){
//        StudentTestScores sts1("John", 3);
//        sts1.setTestScore(70, 0);
//        sts1.setTestScore(80, 1);
//        sts1.setTestScore(90, 2);
//            cout << endl << "Display 1st student -- 1" << endl;
//        sts1.dispalyNameNAllScores();
//        StudentTestScores sts2 = sts1;
//        cout << endl << "Display 2nd student -- 1" << endl;
//        sts2.dispalyNameNAllScores();
//        sts2.setName("Mary");
//        sts2.setTestScore(100, 2);
//        cout << endl << "The name has been changed to Mary and the 3rd score has been changed to 100.";
//        cout << endl << "Display 2nd student -- 2" << endl;
//        sts2.dispalyNameNAllScores();
//        cout << endl << "Display 1st student -- 2" << endl;
//        sts1.dispalyNameNAllScores();
//        /// Copy constructor test
//        // StudentTestScores sts3(sts1);
//        // cout << endl << "Display 3rd student -- 1" << endl;
//        // sts3.dispalyNameNAllScores();
//        /// Overloading operator > test
//        return 0;
//    }
//        

        
        
        
        
        
        
        
        
        
        

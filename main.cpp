    #include <iostream>
    #include "Transformation.h"
    #include "Vector.h"
    using namespace std;
    int main(){
    
    try
    {
        Vector v1{3,12};
        Vector v2{4,-1};
        
        cout<<"Angle : "<<Vector::angleVector(v1,v2)<<endl;

    }
    catch(const char* ex)
    {
        cout<<ex<<endl;
    }
    
    

    return 0;
}
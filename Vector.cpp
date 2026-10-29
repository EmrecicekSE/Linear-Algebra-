#include "Vector.h"
#include <numbers>

    Vector::Vector(int size, double initialValue){
        data.resize(size,initialValue);
    }

    Vector::Vector(initializer_list<double> values){
        
        for(const auto& val : values){
            data.push_back(val);
        }
    }

    Vector::Vector(const vector<double>& values):data(values){}

    void Vector::printVector()const{
        cout<<"[ ";
        for(int i=0;i<static_cast<int>(data.size());i++){
            cout<<data.at(i)<<" ";
        }
        cout<<"] "<<endl;
    }

    int Vector::size()const{
        return data.size();
    }

    bool Vector::isEmpty()const{
        if(size()==0){
            return true;
        }
        return false;
    }

    double& Vector::at(int index){
        return data.at(index);
    }

    double Vector::at(int index)const{
        return data.at(index);
    }

    Vector Vector::operator+(const Vector& other) const{
        if(size()!=other.size()){
            throw "Error :: operator+() for size of the matrix must be equal to other matix";
        }
        const int N=this->size();
        Vector newVector=Vector(N);
        for(int i=0;i<N;i++){
            double value=at(i)+other.at(i);
            newVector.at(i)=value;
        }
        return newVector;
    }

    Vector Vector::operator-(const Vector& other)const{
        if(size()!=other.size()){
            throw "Error :: operator+() for size of the matrix must be equal to other matix";
        }
        const int N=size();
        Vector newVector=Vector(N);
        for(int i=0;i<N;i++){
            double value=at(i)-other.at(i);
            newVector.at(i)=value;
        }
        return newVector;
    }

    Vector Vector::operator*(double scalar)const{
        Vector newVector=Vector(size());
        for(int i=0;i<size();i++){
            double value=at(i)*scalar;
            newVector.at(i)=value;
        }
        return newVector;
    }

    double Vector::dot(const Vector& other) const{
        if(size()!=other.size()){
            throw "Error :: dot() for size of the matrix must be equal to other matix";
        }
        const int N=size();
        double result=0;
        for(int i=0;i<N;i++){
            double value=at(i)*other.at(i);
            result+=value;
        }
        return result;

    }

    bool Vector::isZeroVector()const{
        if(size()<=0){
            throw "Error :: Vector::isZeroVector() for the size must be greater than 0";
        }
        for(int i=0;i<size();i++){
            if(at(i)!=0){
                return false;
            }
        }
        return true;
    }

    
       
    bool Vector::isIndependent(const vector<Vector>& vectors){  // return Rank(A)==N (column number)    Independent: Bütün sütunlar pivot sütunu mu?
        if(vectors.empty()){
            throw "Error ::  Vector::isIndependent(const vector<Vector>& vectors) for vectors cannot be empty";
        }


        for(int i=1;i<static_cast<int>(vectors.size());i++){
            if(vectors.at(0).size()!=vectors.at(i).size()){
                throw "Error :: Vector::isIndependent(const vector<Vector>& vectors) for vectors sizes must be same each other";
            }
        }

        Matrix A=vectorsToMatrix(vectors);   // creating A matrix with vectors 

        int rank=A.rank();

        return rank==A.getColumns();

    }


   

    bool Vector::isLinearCombination(const Vector& target,const vector<Vector>& vectors){ // return rank(A)==rank(A|B)
        if(vectors.empty()){
            throw "Error :: Vector::isLinearCombination(const Vector& target,const vector<Vector>& vectors) for vectors cannot be empty";
        }

        for(int i=1;i<static_cast<int>(vectors.size());i++){
            if(vectors.at(0).size()!=vectors.at(i).size()){
                throw "Error :: Vector::isLinearCombination(const Vector& target,const vector<Vector>& vectors) for vectors sizes must be same each other";
            }
            if(vectors.at(i).size()!=target.size()){
                throw "Error :: Vector::isLinearCombination(const Vector& target,const vector<Vector>& vectors) for vectors sizes must be same each other";
            }
        }
        

        Matrix A=Matrix(vectors.at(0).size(),vectors.size());   // A Matrix
        Matrix augmantedMatrix=Matrix(vectors.at(0).size(),vectors.size()+1); // A|B matrix 

        for(int col=0;col<A.getColumns();col++){    //Fill A matrix
            for(int row=0;row<A.getRows();row++){
                A.at(row,col)=vectors.at(col).at(row);
                augmantedMatrix.at(row,col)=vectors.at(col).at(row);
            }
        }

        for(int r=0;r<augmantedMatrix.getRows();r++){   // Fill A|B matrix
            augmantedMatrix.at(r,augmantedMatrix.getColumns()-1)=target.at(r);
        }

        int rankA=A.rank();
        int rankAugmantedMatrix=augmantedMatrix.rank();

        return rankA==rankAugmantedMatrix;
    }


     bool Vector::doesSpan(const vector<Vector>& vectors){  // Rank(A)==numberOfRows    Span: Bütün satırlarda pivot var mı?
        if(vectors.empty()){
            throw "Error :: doesSpan(const vector<Vector>& vectors) for the vectors cannot be empty";
        }
        
        for(int i=1;i<static_cast<int>(vectors.size());i++){
            if(vectors.at(0).size()!=vectors.at(i).size()){
                throw "Error :: doesSpan(const vector<Vector>& vectors) for the vectors sizes must be same each other";
            }
        }   
        Matrix A=vectorsToMatrix(vectors);
        

        int rankA=A.rank();
        return rankA==A.getRows();
     }

     bool Vector::isBasis(const vector<Vector>& vectors){
        return doesSpan(vectors)&&isIndependent(vectors);
     }

     vector<Vector> Vector::getBasis(const vector<Vector>& vectors){
        if(vectors.empty()){
            throw "Error :: Vector::getBasis(const vector<Vector>& vectors) for the vectors cannot be empty";
        }
        for(int i=1;i<static_cast<int>(vectors.size());i++){
            if(vectors.at(0).size()!=vectors.at(i).size()){
                throw "Error ::  Vector::getBasis(const vector<Vector>& vectors) for the vectors size must be equal each other";
            }
        }
        Matrix A=vectorsToMatrix(vectors);

        

        return A.getColumnSpaceBasis(); // rref getiriyor ve orjinal matrisdekileri alıyor
     }

     Matrix Vector::vectorsToMatrix(const vector<Vector>& vectors){
        if(vectors.empty()){    // check empty
            throw "Error :: Vector:::vectorsToMatrix(const vector<Vector>& vectors) for the vectors cannot be empty";
        }
        for(int i=1;i<static_cast<int>(vectors.size());i++){  // check same size
            if(vectors.at(0).size()!=vectors.at(i).size()){
                throw "Error ::  Vector::vectorsToMatrix(const vector<Vector>& vectors) for the vectors size must be equal each other";
            }
        }
        Matrix A=Matrix(vectors.at(0).size(),vectors.size());   // vreate A matrix

        for(int col=0;col<A.getColumns();col++){    // Fill A matrix
            for(int row=0;row<A.getRows();row++){
                A.at(row,col)=vectors.at(col).at(row);
            }
        }
        return A;    // return A matrix
     }


     
     bool Vector::isOrthonormal(const vector<Vector>& vectors){
        if(!Vector::isOrthogonal(vectors)){     // check it is orthogonal
            return false;
        }

        // every vectors must be unit vector !!! 

        for(int i=0;i<static_cast<int>(vectors.size());i++){
            if(vectors.at(i).norm()!=1){
                return false;
            }
        }
        return true;
     }

     bool Vector::isOrthogonal(const vector<Vector>& vectors){  // iç çarpımlar 0   (inside dot product must be 0 (zero))
        for(int i=0;i<static_cast<int>(vectors.size());i++){
            for(int j=i+1;j<static_cast<int>(vectors.size());j++){
                if(vectors.at(i).dot(vectors.at(j))!=0){
                    return false;
                }
            }
        }
        return true;
     }

     double Vector::norm()const{    // ||v|| (length of vector)
        double result=0;
        for(int i=0;i<this->size();i++){
            result+=pow(at(i),2);
        }
        return sqrt(result);
     }

     double Vector::angleVector(const Vector& v1,const Vector& v2){
        const double dotProduct=v1.dot(v2);
        const double normProduct=v1.norm()*v2.norm();
        if(normProduct==0){
            throw "Error::Vector::angleVector: Zero vector!";
        }
        const double result=acos(dotProduct/normProduct);
        return result*180/numbers::pi;
     }

#include "Matrix.h"
#include "Vector.h"
#include <iostream>
#include <cmath>
using namespace std;

        
        void Matrix::fillMatrix(double initial_val){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    matrix[i][j]=initial_val;
                }
            }
        }

        vector<double> Matrix::getRowArray(const int i)const{
            if(i<0 || i>=getRows()){
                throw "Error: row index out of bounds.";
            }
            vector<double> v;
            v.resize(getColumns());
            for(int j=0;j<getColumns();j++){
                v[j]=at(i,j);
            }
            return v;
        }
        vector<double> Matrix::getColumnArray(int j)const{
            if(j<0 || j>=getColumns()){
                throw "Error : column index out of bounds.";
            }
            vector<double> v;
            v.resize(getRows());
            for(int i=0;i<getRows();i++){
                v[i]=at(i,j);
            }
            return v;
        }

        double Matrix::calculate(vector<double>& v1,vector<double>& v2){
            double sum=0.0;
            for(int i=0;i<static_cast<int>(v1.size());i++){                 // // size() unsigned döndürdüğü için int ile karşılaştırmada uyarı almamak adına int'e dönüştürüyoruz
                sum+=v1.at(i)*v2.at(i);
            }
            return sum;
        }

        bool Matrix::isValidColumnForRREF(vector<double>& v)const{
            int one=0;
            int zero=0;
            for(int i=0;i<getRows();i++){
                if(v.at(i)==1){
                    one++;
                }
                if(v.at(i)==0){
                    zero++;
                }
            }
            return (one+zero)==getRows() && one==1;
        }

        Matrix Matrix::makeIdentityMatrix()const{
            if(!isSquare()){
                throw "Error :: makeIdentityMatrix() for the matrix must be square matrix.";
            }
            Matrix IdentitiyMatrix=Matrix(getRows(),getColumns());
            for(int row=0;row<IdentitiyMatrix.getRows();row++){
                for(int col=0;col<IdentitiyMatrix.getColumns();col++){
                    if(row==col){
                        IdentitiyMatrix.at(row,col)=1;
                    }
                    else{
                        IdentitiyMatrix.at(row,col)=0;
                    }
                }
            }
            return IdentitiyMatrix;
        }

        Matrix::Matrix(int rows,int cols,double initial_val){   //Constructor
            this->rows=rows;
            this->cols=cols;
            matrix.resize(rows,vector<double>(cols));
            fillMatrix(initial_val);
        }

        Matrix::Matrix(initializer_list<initializer_list<double> > values){
            rows=values.size();
            if(rows==0){
                cols=0;
                return;
            }
            cols=values.begin()->size();
            matrix.resize(rows,vector<double>(cols));

            int i=0;
            for(const auto& row : values){

                if(static_cast<int>(row.size()) != cols){   // row.size() unsigned döndürdüğü için int türüne dönüştürülüyor.
                    throw "Error::Matrix::Initializer rows have different sizes";
                }

            int j = 0;

            for(double value : row){
                matrix[i][j] = value;
                j++;
            }

            i++;
        }
        }

        int Matrix::getRows()const{return rows;}
        int Matrix::getColumns()const{return cols;}

        const double& Matrix::at(int i,int j)const{
            if(i>=0 && j>=0 && i<getRows() && j<getColumns()){
                return matrix[i][j];
            }
            throw "Error::Matrix::at() for i or j out of bounds";
        }

        double& Matrix::at(int i,int j){
            if(i>=0 && j>=0 && i<getRows() && j<getColumns()){
                return matrix[i][j];
            }
            throw "Error::Matrix::at() for i or j out of bounds";
        }

        void Matrix::print()const{
            for(int i=0;i<getRows();i++){
                for(int j=0;j<getColumns();j++){
                    if(j==0){
                        cout<<"| ";
                    }
                    if(j==getColumns()-1){
                        cout<<at(i,j)<<" |";
                        cout<<endl;
                        continue;
                    }
                    cout<<at(i,j)<<" ";
                }
            }
        }

        double Matrix::trace()const{
            if(!isSquare()){
                throw "Error :: Matrix::trace() for the matrix must be square matrix.";
            }
            double result=1;
            const int N=getRows();
            for(int i=0;i<N;i++){
                result+=at(i,i);
            }
            return result;
        }

        bool Matrix::isSameSize(const Matrix& A)const{
            return (A.getRows()==this->getRows())&&(this->getColumns()==A.getColumns());
        }

        Matrix Matrix::add(const Matrix& A){
            if(!isSameSize(A)){
                throw "Boyut uyuşmazlığı";
            }
            Matrix C=Matrix(getRows(),getColumns());

            for(int i=0;i<C.getRows();i++){
                for(int j=0;j<C.getColumns();j++){
                    C.at(i,j)=this->at(i,j)+A.at(i,j);
                }
            }
            return C;
        }

        Matrix Matrix::subtarct(const Matrix& A){
            if(!isSameSize(A)){
                throw "Boyut uyuşmazlığı";
            }
            Matrix C=Matrix(getRows(),getColumns());

            for(int i=0;i<C.getRows();i++){
                for(int j=0;j<C.getColumns();j++){
                    C.at(i,j)=this->at(i,j)-A.at(i,j);
                }
            }
            return C;            
        }

        Matrix Matrix::skalerMultiply(const double k){
            Matrix C=Matrix(getRows(),getColumns());

            for(int i=0;i<C.getRows();i++){
                for(int j=0;j<C.getColumns();j++){
                    C.at(i,j)=at(i,j)*k;
                }
            }
            return C;
        }
        

        Matrix Matrix::matrixMultiplaction(const Matrix& A){
            if(getColumns()!=A.getRows()){
                throw "Error::Matrix::matrixMultiplaction for undefined";
            }
             Matrix C=Matrix(getRows(),A.getColumns());

             for(int i=0;i<getRows();i++){
                vector<double> takeRow=getRowArray(i);
                double value=0.0;
                for(int j=0;j<A.getColumns();j++){
                    vector<double> takeCol=A.getColumnArray(j);
                    value=calculate(takeRow,takeCol);
                    C.at(i,j)=value;
                }
             }
             return C;
        }
        
        /*Matrix matrixMultiplaction(const Matrix& A){    // optimize
            if(this->getColumns()!=A.getRows()){
                throw "Error::Matrix::matrixMultiplaction for undefined";
            }
            Matrix C=Matrix(getColumns(),A.getRows());
            
            for(int i=0;i<getRows();i++){

                for(int j=0;j<A.getColumns();j++){

                    double sum=0.0;

                    for(int k=0;k<getColumns();k++){
                        sum+=at(i,k)*A.at(k,j);
                    }
                    
                    C.at(i,j)=sum;
                }
            }
            return C;
        }*/

        Matrix Matrix::transpose()const{
            Matrix m=Matrix(getColumns(),getRows());
            for(int i=0;i<m.getRows();i++){
                for(int j=0;j<m.getColumns();j++){
                    m.at(i,j)=at(j,i);
                }
            }
            return m;
        }

        Matrix Matrix::createZeroMatrix(const int row,const int column){
            if(row<=0||column<=0){
                throw "Error : Matrix::createZeroMatrix() for row or columnc mustn't be zero or negative";
            }
            Matrix zeroMatrix=Matrix(row,column);
            return zeroMatrix;
        }



        bool Matrix::isSquare()const{return getRows()==getColumns();}

        bool Matrix::isIdentity()const{
            if(!isSquare()){
                throw "Error :: isIdentity() for the matrix must be square matrix.";
            }

            for(int i=0;i<getRows();i++){
                for(int j=0;j<getColumns();j++){
                    if(i==j && at(i,j)!=0){
                        return false;
                    }
                    else if(i!=j && at(i,j)!=0){
                        return false;
                    }
                }
            }
            return true;
        }

        void Matrix::swapRows(const int i,const int j){
            if(i<0 || j<0 || i>=getRows() || j>=getRows()){
                throw "Error :: swapRows() for index is out of bounds.";
            }
            vector<double> v1=getRowArray(i);
            vector<double> v2=getRowArray(j);

            for(int col=0;col<getColumns();col++){
                at(i,col)=v2[col];
                at(j,col)=v1[col];
            }
        }
        void Matrix::scaleRow(const int rowIndex,const double k){
            if(rowIndex<0 ||  rowIndex>=getRows() ){
                throw "Error :: scaleRow() for index is out of bounds.";
            }

            for(int col=0;col<getColumns();col++){
                at(rowIndex,col)*=k;
            }
        }
        void Matrix::scaleMatrix(const double k){
            for(int i=0;i<getRows();i++){
                scaleRow(i,k);
            }
        }

        void Matrix::addRow(const int targetRow, const int sourceRow,const double scalar){   // Ai=Ai+Aj;
            vector<double> v1=getRowArray(sourceRow);
            for(int i=0;i<getColumns();i++){
                v1[i]*=scalar;
            }
            for(int col=0;col<getColumns();col++){
                at(targetRow,col)=at(targetRow,col)+v1[col];
            }

            
        }

        bool Matrix::isRowZero(const int rowIndex)const{
            if(rowIndex<0 || rowIndex>=getRows()){
                throw "Error :: isRowZero() for row index out of bounds.";
            }
            for(int col=0;col<getColumns();col++){
                if(abs(at(rowIndex,col)) > 1e-9){
                    return false;
                }
            }
            return true;
        }

        bool Matrix::isColumnZero(const int columnIndex)const{
            if(columnIndex<0 || columnIndex>=getColumns()){
                throw "Error :: isColumnZero() for row index out of bounds.";
            }
            for(int row=0;row<getRows();row++){
                if(abs(at(row,columnIndex)) > 1e-9){
                    return false;
                }
            }
            return true;
        }

        bool Matrix::isRef()const{
            int last_pivot_col=-1;
            bool seen_zero_row=false;

            for(int i=0;i<getRows();i++){
                if(isRowZero(i)){
                    seen_zero_row=true;
                    continue;
                }
                for(int j=0;j<getColumns();j++){
                    if(abs(at(i, j)) > 1e-9){   // at(i,j)!=0   (sıfırdan farklı bir eleman bulduk).
                      
                        if(seen_zero_row){
                            
                            return false;
                        }

                        if(abs(at(i, j) - 1.0) > 1e-9){ // at(i,j)!=1   (eleman 1'e eşit değilse false)
                            
                            return false;
                        }

                        if(j<=last_pivot_col){
                            
                            return false;
                        }
                        last_pivot_col=j;
                        break;
                    }
                }
            }
            return true;
        }
       
        bool Matrix::isRRef()const{
            int last_pivot_col=-1;
            bool seen_zero_row=false;

            for(int i=0;i<getRows();i++){
                if(isRowZero(i)){
                    seen_zero_row=true;
                    continue;
                                            }
                for(int j=0;j<getColumns();j++){
                    if(abs(at(i, j)) > 1e-9){       // at(i,j)!=0   (sıfırdan farklı bir eleman bulduk).

                        if(seen_zero_row){
                            
                            return false;
                        }

                         if(abs(at(i, j) - 1.0) > 1e-9){ // at(i,j)!=1   (eleman 1'e eşit değilse false)
                            
                            return false;
                        }

                        if(j<=last_pivot_col){
                            
                            return false;
                        }

                        vector<double> v=getColumnArray(j);
                        if(!isValidColumnForRREF(v)){
                            
                            return false;
                        }
                        last_pivot_col=j;
                        break;
                    }
                }
            }
            return true;
        }

        bool Matrix::isLowerMatrix()const{
            if(!isSquare()){
                throw "Error: isLowerMatrix() for this matrix must be square matrix";
            }
            for(int i=0;i<getRows();i++){
                for(int j=0;j<getColumns();j++){
                    if(i==j && abs(at(i, j) - 1.0) > 1e-9){ // at(i,j)!=1   (eleman 1'e eşit değilse false)
                       return false;
                    }
                    if(j>i && abs(at(i, j)) > 1e-9){    // at(i,j)!=0   (sıfırdan farklı bir eleman bulduk).
                        return false;
                    }
                }
            }
            return true;
        }

        bool Matrix::isUpperMatrix()const{
            if(!isSquare()){
                throw "Error: isUpperMatrix() for this matrix must be square matrix";
            }
            for(int i=0;i<getRows();i++){
                for(int j=0;j<getColumns();j++){
                    if(i>j && abs(at(i, j)) > 1e-9){    // at(i,j)!=0   (sıfırdan farklı bir eleman bulduk).
                        return false;
                    }
                }
            }
            return true;
        }

        bool Matrix::isSymmetricMatrix()const{
            if(!isSquare()){
                throw "Error : Matrix::isSymmetricMatrix() for the matrix must be square matrix.";
            }
            Matrix transposeMatrix=transpose();
            int N=getRows();
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    if(this->at(i,j)!=transposeMatrix.at(i,j)){
                        return false;
                    }
                }
            }
            return true;
        }

        bool Matrix::isInvertible()const{
            if(!isSquare()){
                return false;
            }
            if(determinant()==0){
                return false;
            }
            return true;
        }
        bool Matrix::hasNonTrivialSolutionsForSquareMatrix()const{
            if(!isSquare()){
                throw "Error :: Matrix::hasNonTrivialSolutionsForSquareMatrix() for this method works just on square matrix.";
            }
            if(determinant()==0){
                return true;
            }
            return false;
        }


        bool Matrix::hasUniqueSolutionForSquareMatrix()const{   // if det(A)!=0 then it has unique solution
            if(!isSquare()){
                throw "Error :: Matrix::hasUniqueSolution() for the matrix must be square matrix";
            }
            double numberOfDeterminant=determinant();
            if(numberOfDeterminant!=0){
                return true;
            }
            else{
                return false;
            }
        }


        
        
        Matrix Matrix::toUpperTriangular(int& swapCount) const{
            if(!isSquare()){
                throw "Error: toUpperTriangular() for this matrix must be square matrix";
            }
            Matrix newMatrix=*this;
            
            
            for(int col=0;col<newMatrix.getColumns();col++){

                double pivot=newMatrix.at(col,col);

                if(pivot==0){
                    for(int r=0;r<newMatrix.getRows();r++){
                        if(newMatrix.at(r,col)!=0){
                            newMatrix.swapRows(r,col);
                            swapCount++;
                            break;
                        }
                    }
                    pivot=newMatrix.at(col,col);
                }
                for(int row=0;row<newMatrix.getRows();row++){
                    if(row>col){
                        double targetNumber=newMatrix.at(row,col);
                        double factor=targetNumber/pivot;
                        newMatrix.addRow(row,col,-factor);
                    }
                }
            }
            
            return newMatrix;
        }

        // override
        Matrix Matrix::toUpperTriangular() const{
            if(!isSquare()){
                throw "Error: toUpperTriangular() for this matrix must be square matrix";
            }
            Matrix newMatrix=*this;
            
            
            for(int col=0;col<newMatrix.getColumns();col++){

                double pivot=newMatrix.at(col,col);

                if(pivot==0){
                    for(int r=col+1;r<newMatrix.getRows();r++){
                        if(newMatrix.at(r,col)!=0){
                            newMatrix.swapRows(r,col);
                            break;
                        }
                    }
                    pivot=newMatrix.at(col,col);
                }
                for(int row=0;row<newMatrix.getRows();row++){
                    if(row>col){
                        double targetNumber=newMatrix.at(row,col);
                        double factor=targetNumber/pivot;
                        newMatrix.addRow(row,col,-factor);
                    }
                }
            }
            
            return newMatrix;
        }

        
        
        Matrix Matrix::toLowerTriangular()const{        
            if(!isSquare()){
                throw "Error: toLowerTriangular() for this matrix must be square matrix";
            }

            Matrix newMatrix=makeIdentityMatrix();

            Matrix copyMatrix=*this;

            for(int col=0;col<copyMatrix.getColumns();col++){

                double pivot=copyMatrix.at(col,col);
                if(pivot==0){
                    for(int r=col+1;r<copyMatrix.getRows();r++){
                        if(copyMatrix.at(r,col)!=0){
                            copyMatrix.swapRows(r,col);
                            break;
                        }
                    }
                    pivot=copyMatrix.at(col,col);
                }

                for(int row=0;row<copyMatrix.getRows();row++){
                    if(row>col){
                        double targetNumber=copyMatrix.at(row,col);
                        double factor=targetNumber/pivot;
                        copyMatrix.addRow(row,col,-factor);
                        newMatrix.at(row,col)=factor;
                    }
                }
            }
            return newMatrix;    
        }




        Matrix Matrix::toREF() const {
            Matrix RefMatrix=*this;
            int leadRow=0,leadCol=0;

            while(leadRow<RefMatrix.getRows() && leadCol<RefMatrix.getColumns()){

                bool thereExistPivot=false;
                for(int i=leadRow;i<RefMatrix.getRows();i++){
                    if(abs(RefMatrix.at(i,leadCol)) > 1e-9){
                        thereExistPivot=true;
                    }
                }
                if(!thereExistPivot){
                    leadCol++;
                    continue;
                }


                

                for(int pivotRow=leadRow;pivotRow<RefMatrix.getRows();pivotRow++){
                    if(abs(RefMatrix.at(pivotRow,leadCol)) > 1e-9){
                        if(pivotRow!=leadRow){
                            RefMatrix.swapRows(pivotRow,leadRow);
                            
                        }
                        break;
                    }
                }
                RefMatrix.scaleRow(leadRow,1.0/RefMatrix.at(leadRow,leadCol));

                for(int i=leadRow+1;i<RefMatrix.getRows();i++){
                    double k=RefMatrix.at(i,leadCol);
                    RefMatrix.addRow(i,leadRow,-k);
                }
                leadRow++;
                leadCol++;
            }
            return RefMatrix;
     }


     Matrix Matrix::toRREF()const{
        Matrix rrefMatrix=toREF();

        int startRow=rrefMatrix.getRows()-1;
        int startCol=0;

        while(startRow>=0){
            for(int col=startCol;col<rrefMatrix.getColumns();col++){
                if(rrefMatrix.at(startRow,col)==1){ // pivot yer startRow,col
                    for(int i=startRow-1;i>=0;i--){
                        rrefMatrix.addRow(i,startRow,-rrefMatrix.at(i,col));
                    }
                    break;
                }
            }
            startRow--;
        }   
        return rrefMatrix;
     }



        Matrix Matrix::solveMatrix(const Matrix& B)const{
            if(B.getColumns()!=1 || this->getRows()!=B.getRows()){
                throw "Error :: solveMatrix(const Matrix& B) for B matrix has a wrong column or rows. ";
            }

            // lux=b ly=b ux=y;

            Matrix L=this->toLowerTriangular();
            Matrix U=this->toUpperTriangular();
            Matrix Y=Matrix(getRows(),B.getColumns());
            Matrix X=Matrix(getRows(),B.getColumns());

            // Let's solve LY=B;
            
            for(int i = 0; i < L.getRows(); i++){
                double answer = B.at(i,0);
                
                for(int j = 0; j < i; j++){     // Sadece i'den küçük sütunlara (köşegenin soluna) bakıyoruz:

                    answer -= L.at(i, j) * Y.at(j, 0);  // L'deki katsayı ile daha önce bulduğumuz Y değerini çarpıp çıkarıyoruz:   (L.at(i, j)=katsayi //// Y.at(j, 0)=katsayinin yanindaki gerçek sayi)

                }
                Y.at(i,0) = answer;
            }

            // Okey we find the y results,so Lets solve Ux=Y

            for(int i=U.getRows()-1;i>=0;i--){
                double answer=Y.at(i,0);
                for(int j=U.getColumns()-1;j>=i;j--){
                    if(i==j){
                        answer/=U.at(i,j);
                    }
                    else{
                        answer-=U.at(i,j)*X.at(j,0);
                    }
                }
                X.at(i,0)=answer;
            }
            return X;
        }

        double Matrix::determinant()const{  // det(A) = det(L) . det(U)  and a upper or lower matrix determinant equals diagonal multiply
            if(!isSquare()){
                throw "Error :: Determinant() for the matrix must be square matrix";
            }
            int swapCount=0;
            Matrix U=toUpperTriangular(swapCount);
            double result=1;
            for(int i=0;i<U.getRows();i++){
                result*=U.at(i,i);
            }
            if(swapCount%2==0){
                return result;
            }
            else{
                return -result;
            }
        }



        /*
            * MANTIK: A * A^(-1) = I eşitliğinde Birim Matrisin sütunları (e_0, e_1, ..., e_n-1)'dir.
            * A^(-1)'in her bir sütununu bulmak için sırayla şu sistemler çözülür:
            *   A * x_0 = [1, 0, 0, ...]^T
            *   A * x_1 = [0, 1, 0, ...]^T
        */
       
        Matrix Matrix::inverse()const{
            if(!isSquare()){
                throw "Error :: inverse() for the matrix must be square matrix";
            }
            if(determinant()==0){
                throw "The inverse of the matrix does not exist. ( the determinant equals zero (0) )";
            }

            Matrix inverseMatrix=Matrix(getRows(),getColumns());
            
            for(int i=0;i<getRows();i++){

                Matrix e(getRows(),1);
                e.at(i,0)=1.0;
                
                Matrix answer_column=this->solveMatrix(e);

                for(int j=0;j<getColumns();j++){
                    inverseMatrix.at(j,i)=answer_column.at(j,0);
                }
            }
            return inverseMatrix;
        }
        
        /*Matrix Matrix::inverse()const{    A^-1=adj()/determinant()
            if(!isSquare()){    
                throw "Error :: inverse() for the matrix must be square matrix";
            }
            if(determinant()==0){
                throw "The inverse of the matrix does not exist. ( the determinant equals zero (0) )";
            }
            Matrix adjMatrix=adj();    
            double determinantOfMatrix=1/determinant();
            Matrix InverseOfMatrix=adjMatrix.skalerMultiply(determinantOfMatrix);
            return InverseOfMatrix;
        }*/
        

        Matrix Matrix::getMinorMatrix(int row,int col)const{
            if(!isSquare()){
                throw "Error :: getMinorMatrix() for the matrix must be square matrix";
            }
            if(getRows()<2 || getColumns() < 2){
                throw "Error :: getMinorMatrix() for the matrix at least 2x2 to get to minor";
            }
            if(row<0 || col <0 || row>=getRows() || col>=getColumns()){
                throw "Error: getMinorMatrix() for row or column index out of bounds.";
            }

            Matrix minorMatrix=Matrix(getRows()-1,getColumns()-1);

            int minorRow=0;

            for(int r=0;r<getRows();r++){
                if(r==row){
                    continue;
                }

                int minorCol=0;

                for(int c=0;c<getColumns();c++){
                    if(c==col){
                        continue;
                    }
                    minorMatrix.at(minorRow,minorCol)=at(r,c);
                    minorCol++;
                }
                minorRow++;
            }
            
            return minorMatrix;
        }

        double Matrix::minor(int row,int col)const{
            if(!isSquare()){
                throw "Error :: minor() for the matrix must be square matrix";
            }
            if(getRows()<2 || getColumns() < 2){
                throw "Error :: minor() for the matrix at least 2x2 to get to minor";
            }
            if(row<0 || col <0 || row>=getRows() || col>=getColumns()){
                throw "Error: minor() for row or column index out of bounds.";
            }

            Matrix minorMatrix=getMinorMatrix(row,col);

            return minorMatrix.determinant();
        }

        double Matrix::cofactor(int row,int col)const{
            if(!isSquare()){
                throw "Error :: cofactor() for the matrix must be square matrix";
            }
            if(getRows()<2 || getColumns() < 2){
                throw "Error :: cofactor() for the matrix at least 2x2 to get to minor";
            }
            if(row<0 || col <0 || row>=getRows() || col>=getColumns()){
                throw "Error: cofactor() for row or column index out of bounds.";
            }

            double minorMatrixValue=minor(row,col);

            if((row+col)%2==0){
                return minorMatrixValue;
            }
            else{
                return -minorMatrixValue;
            }
        }

        Matrix Matrix::cofactorMatrix()const{
            if(!isSquare()){
                throw "Error :: cofactorMatrix() for the matrix must be square matrix.";
            }
            if (getRows() < 2) {
                throw "Error: Matrix must be at least 2x2.";
            }

            Matrix cofactorMatrix=Matrix(getRows(),getColumns());
            for(int r=0;r<getRows();r++){
                for(int c=0;c<getColumns();c++){
                    double cofactorValue=cofactor(r,c);
                    cofactorMatrix.at(r,c)=cofactorValue;
                }
            }
            return cofactorMatrix;
        }

        Matrix Matrix::adj()const{
            if(!isSquare()){
                throw "Error:: adj() for the matrix must be square matrix.";
            }

            Matrix cofMatrix=cofactorMatrix();
            Matrix adjMatrix=cofMatrix.transpose();
            return adjMatrix;

        }


        Matrix Matrix::createIdentityMatrix(const int n){
            if(n<=0){
                throw "Error :: Matrix::createIdentityMatrix() for n must be greater than 0";
            }
            Matrix identityMatrix=Matrix(n,n);
            for(int i=0;i<n;i++){
                identityMatrix.at(i,i)=1;
            }
            return identityMatrix;
        }



        int Matrix::rank()const{
            Matrix refMatrix=toREF();
            int result=0;
            for(int row=0;row<refMatrix.getRows();row++){
                for(int col=0;col<refMatrix.getColumns();col++){
                    if(refMatrix.at(row,col) == 1){
                        result++;
                        break;
                    }
                }
            }
            return result;
        }

        int Matrix::nullity()const{ // Rank(A) + nullity(A) == sütun sayısı (number of column)
            return rank()-getColumns();
        }



        vector<Vector> Matrix::getColumnSpaceBasis()const{      // burda pivotları bulduktan sonra orjinal matrixdeki sütunları almalısın
            Matrix refMatrix=toREF();
            vector<Vector> basis;

             for(int row=0;row<refMatrix.getRows();row++){
                for(int col=0;col<refMatrix.getColumns();col++){
                    if(abs(refMatrix.at(row,col)) > 1e-9){
                        vector<double> v=getColumnArray(col);
                        Vector vec=Vector(v);
                        basis.push_back(vec);
                        break;
                    }
                    
                }
            }
            return basis;
        }


        vector<Vector> Matrix::getRowSpaceBasis()const{ // burda ise ref formuna getirdikten sonra refdeki matristen satır halinde alıp basise koyuyoruz
            Matrix refMatrix=toREF();
            vector<Vector> basis;


            for(int row=0;row<refMatrix.getRows();row++){
                for(int col=0;col<refMatrix.getColumns();col++){
                    if(abs(refMatrix.at(row,col)) > 1e-9){
                        vector<double> v=refMatrix.getRowArray(row);
                        Vector vec=Vector(v);
                        basis.push_back(vec);
                        break;
                    }
                    
                }
            }
            return basis;
        }
        

        vector<Vector> Matrix::getNullSpaceBasis() const{
            Matrix rrefMatrix = toRREF();

            
            vector<int> pivotCols;
            vector<int> freeCols;


            for(int row=0;row<rrefMatrix.getRows();row++){
                for(int col=0;col<rrefMatrix.getColumns();col++){
                    if(abs(rrefMatrix.at(row,col)) > 1e-9){
                        pivotCols.push_back(col);
                        break;
                    }    
                }
            }

            
            
            for(int i=0;i<rrefMatrix.getColumns();i++){
                bool isFree=true;
                for(int j=0;j<static_cast<int>(pivotCols.size());j++){
                    if(pivotCols.at(j)==i){
                        isFree=false;
                    }
                }
                if(isFree){
                    freeCols.push_back(i);
                }
            }

            vector<Vector> freeVectors; // [0,0,0,1]

            for(int i=0;i<static_cast<int>(freeCols.size());i++){
                Vector v=Vector(rrefMatrix.getColumns());
                int n=freeCols.at(i);
                v.at(n)=1;
                freeVectors.push_back(v);
            }

            for(size_t i=0; i<freeVectors.size(); i++){
                vector<double> v = rrefMatrix.getColumnArray(freeCols[i]);

                for(size_t k=0; k<pivotCols.size(); k++){
                    double coef = -v.at(k);
                    freeVectors.at(i).at(pivotCols[k]) = coef;
                }
            }


            return freeVectors;
        }






// Van Toan Vo: 5550006156
#ifndef MESA_CISC187_BIGINT_H
#define MESA_CISC187_BIGINT_H
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <utility>
#include <stack>

namespace mesa{
class BigInt{
private:
    std::vector<int> bignum;
public:
    static const int zero = 0;
    BigInt(){
        bignum={zero};
    }
    BigInt(const std::string& number){
        std::size_t found = number.find_first_not_of("-0");
            if(number=="0"||found==std::string::npos){
                bignum.push_back(0);
            }else{
                if(found!=std::string::npos){
                    while(found<number.size()){
                        if(isdigit(number[found])){
                            bignum.push_back(number[found]-'0');
                            found++;
                        }else{
                            found = number.size();
                        }
                    }
                }
            }
    }
    BigInt(const BigInt& other)
    : bignum{other.bignum}
    {
        std::copy(other.bignum.begin(), other.bignum.end(), bignum.begin());
    }

    BigInt(BigInt&& other) noexcept
    : bignum{std::move(other.bignum)}
    {}

    BigInt& operator=(const BigInt& other){
        BigInt(other).swap(*this);
        return *this;
    }
    ~BigInt()=default;
    inline
    BigInt& operator=(BigInt&& other) noexcept{
        bignum = std::move(other.bignum);
        return *this;
    }
    void swap(BigInt& rhs){
        std::swap(bignum, rhs.bignum);
    }
    size_t size(){
        return bignum.size();
    }
    std::vector<int>::iterator begin(){
        return bignum.begin();
    }
    std::vector<int>::iterator end(){
        return bignum.end();
    }
    inline
    friend std::ostream& operator<<(std::ostream& os, const BigInt& outstream){
        for(unsigned i =0; i<outstream.bignum.size(); ++i){
            os<<outstream.bignum[i];
        }
        return os;
    }
    inline
    BigInt& operator+=(BigInt& other){
        adding(*this, other);
        return *this;
    }
    inline
    BigInt& operator*=(const BigInt& other){
        multiplying(*this, other);
        return *this;
    }
    inline
    bool operator==(const BigInt& rhs){
        return std::equal(bignum.begin(), bignum.end(), rhs.bignum.begin());
    }
        
    void adding(BigInt& x, BigInt& y){
        unsigned digit = 0;
        bool base = false;
        if(x.bignum.size()==y.bignum.size()){
            for(unsigned i = size()-1; i!=(unsigned)-1; --i){
                if(base){
                    x.bignum[i]+=1;
                    base = false;
                }
                digit = x.bignum[i] + y.bignum[i];
                if(digit>=10&&i!=0){
                    digit%= 10;
                    base = true;
                }
                if(digit>=10&&i==0){
                    x.bignum[i] = digit%10;
                    x.bignum.insert(x.bignum.begin(),(digit/10)%10);
                }else{x.bignum[i] = digit;}
            }
        }else if(x.bignum.size()>y.bignum.size()){
            int k = y.bignum.size()-1;
            bool end_ = false;
            for(unsigned i = size()-1; i!=(unsigned)-1; --i){
                if(base){
                    x.bignum[i]+=1;
                    base = false;
                }
                if(k>0){
                    digit = x.bignum[i] + y.bignum[k];
                }else if(k==0&&end_==false){
                    digit = x.bignum[i] + y.bignum[k];
                    end_ = true;
                }else{
                    digit = x.bignum[i];
                }
                if(digit>=10&&i!=0){
                    digit%= 10;
                    base = true;
                }
                if(digit>=10&&i==0){
                    x.bignum[i] = digit%10;
                    x.bignum.insert(x.bignum.begin(),(digit/10)%10);
                }else{x.bignum[i] = digit;}
                if(k!=0){k-=1;}
            }
        }else {
            int k = x.bignum.size()-1;
            bool end_ = false;
            for(unsigned i = y.bignum.size()-1; i!=(unsigned)-1; --i){
                if(base){
                    y.bignum[i]+=1;
                    base = false;
                }
                if(k>0){
                    digit = y.bignum[i] + x.bignum[k];
                }else if(k==0&&end_==false){
                    digit = y.bignum[i] + x.bignum[k];
                    end_ = true;
                }else{
                    digit = y.bignum[i];
                }
                if(digit>=10&&i!=0){
                    digit%= 10;
                    base = true;
                }
                if(digit>=10&&i==0){
                    y.bignum[i]=digit%10;
                    y.bignum.insert(y.bignum.begin(),(digit/10)%10);
                }else{y.bignum[i] = digit;}
                if(k>0){k-=1;}
            }
            x.bignum = y.bignum;
        }
    }

    void multiplying(BigInt& x, const BigInt& y){
      BigInt result,temp;
        if(x.bignum[0]!=zero&&y.bignum[0]!=zero){
          temp.bignum.clear();
          unsigned count_ = 0;
          unsigned factor = 0;
          unsigned digit = 0;
          bool base = false;
          for(unsigned j = y.bignum.size()-1; j!=(unsigned)-1; --j){
            for(unsigned i = size()-1; i!=(unsigned)-1; --i){
                digit = y.bignum[j]*x.bignum[i];
                if(base){
                    digit +=factor;
                    factor=0;
                    base=false;
                }
                if(digit>=10&&i!=0){
                    factor = (digit/10)%10;
                    digit = digit%10;
                    base = true;
                }
                if(digit>=10&&i==0){
                    factor = (digit/10)%10;
                    digit = digit%10;
                }
                temp.bignum.push_back(digit);
                if(i==0&&factor>0){
                    temp.bignum.push_back(factor);
                    factor =0;
                }
              }
                count_+=1;
                if(temp.bignum.size()>1){
                    std::reverse(temp.bignum.begin(),temp.bignum.end());
                }
                if(j<=(y.bignum.size()-2)){
                    for(unsigned n = 1; n<count_; n++){
                        temp.bignum.push_back(0);
                    }
                }
                result+=temp;
                temp.bignum.clear();
          }
        }
        x = result;
    }
    
    //this divide function is used to optimize the power calculation only
    //because it only works with integer numbers and gives the result of an integer.
    BigInt operator/(const int y){
        BigInt result;
        result.bignum.clear();
        unsigned divided_number =0;
        bool odd = false;
        for(unsigned i = 0; i<bignum.size();++i){
                unsigned temp = 0;
                if(odd){
                    bignum[i] +=10;
                    odd = false;
                }
                if(bignum[0]==1 && i==0){
                    temp = 10;
                    ++i;
                }
                if((bignum[i]%y)==0){
                    divided_number = (bignum[i] + temp)/y;
                }else{
                    divided_number = (bignum[i]+temp)/y;
                    odd = true;
                }
                result.bignum.push_back(divided_number);
        }
        return result;
    }
  
    BigInt pow(BigInt n){
        BigInt zero{"0"};
        if(n==zero){return BigInt{"1"};}
        if((n.bignum.size()==1)&&(n.bignum[0]==1)){return *this;}
        BigInt tmp = pow(n/2);
        tmp*=tmp;
        if((n.bignum[n.bignum.size()-1]%2)==1){
            tmp*=*this;
        }
        return tmp;
    }
};

struct Handler{
virtual ~Handler()= default;
virtual bool handle(std::stack<BigInt>& operands, const std::string& token) const = 0;
};

struct Add: public Handler {
    bool handle(std::stack<BigInt>& operands, const std::string& token) const override{
        if(token!="+"){
            return false;
        }
        if(operands.size()>=2){
            BigInt first = operands.top();
            operands.pop();
            BigInt second = operands.top();
            operands.pop();
            first+=second;
            operands.push(first);
        }else{ 
            std::cout<<"Invalid argument: Not enough operands to execute add operation.\n";
        }
        return true;
    }
};

struct Multiply: public Handler {
    bool handle(std::stack<mesa::BigInt>& operands, const std::string& token) const override{
        if(token!="*"){
            return false;
        }
        if(operands.size()>=2){
            BigInt first = operands.top();
            operands.pop();
            BigInt second = operands.top();
            operands.pop();
            first*=second;
            operands.push(first);
        }else{
            std::cout<<"Invalid argument: Not enough operands to execute multiply operation.\n";
        }
        return true;
    }
};
struct Power: public Handler {
    bool handle(std::stack<mesa::BigInt>& operands, const std::string& token) const override{
        if(token!="^"){
            return false;
        }
        if(operands.size()>=2){
            BigInt exponent = operands.top();
            operands.pop();
            BigInt base = operands.top();
            operands.pop();
            operands.push(base.pow(exponent));
        }else{
            std::cout<<"Invalid argument: Not enough operands to execute power operation.\n";
        }
        return true;
    }
};
struct OperandPusher: public Handler {
    bool handle(std::stack<BigInt>& operands, const std::string& token) const override{
        for(unsigned i = 0; i<token.size(); i++){
            if(!isdigit(token[i])){
                return false;
            }
        }
            operands.push(BigInt{token});
            return true;
    }
};
}//end of namespace mesa
inline
bool operator!=(mesa::BigInt& lhs, mesa::BigInt& rhs){
    return !(lhs==rhs);
}
inline
mesa::BigInt operator+(mesa::BigInt lhs, mesa::BigInt rhs){
    lhs+=rhs;
    return lhs;
}
inline
mesa::BigInt operator*(mesa::BigInt lhs, const mesa::BigInt& rhs){
    lhs*=rhs;
    return lhs;
}
#endif

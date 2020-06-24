template<typename T>
std::vector<T> RangeCopy(std::vector<T> v,int startIndex, int count)
{
    return std::vector<T>(v.begin() + startIndex,v.begin() + count);
}
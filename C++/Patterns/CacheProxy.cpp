
template<typename K, typename V>
class LruCache
{
public:
    bool Get(int k, int& outV);
    void Put(int k, int v);
};

class IDecompressor {
public:
    virtual int Decompress(int key); 
};

class Decompressor : public IDecompressor {
public:
    int Decompress(int key) override { 
        // todo: CPU-intensive task
        return 0; 
    }
};

class CachedDecompressor : public IDecompressor {
private:
    LruCache<int, int> m_cache_data;
    Decompressor* m_decompressor;
public:
    
    int Decompress(int key) override { 
        int result = 0;
    	if (m_cache_data.Get(key, result)) {
            return result;
        }
        return m_decompressor->Decompress(key);
    }
};

int main(int argc, const char** argv)
{
    return 0;
}
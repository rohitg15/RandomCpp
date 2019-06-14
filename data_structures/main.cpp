#include "union_find.h"
#include "morris_traversal.h"
#include "string_utils.h"
#include "hash_table.h"
#include <sstream>
#include <unordered_map>
#include <chrono>
#include "thread_safe_queue.h"
#include "thread_pool_queue.h"
#include "thread_pool.h"
#include "thread_context.h"
#include <thread>
#include <chrono>

using Iitem = Item<int>;
using Collection = std::vector<Iitem>;

void TestUnionFind()
{

    Collection items{Iitem(0, 0), Iitem(1,1), Iitem(2,2), Iitem(3,3), Iitem(4,4), Iitem(5,5)};
    UnionFind<int> uf{items};


    // merge (0, 1) , (2, 3), (1, 4)
    uf.MergeSet(items[0], items[1]);
    uf.MergeSet(items[2], items[3]);
    uf.MergeSet(items[1], items[4]);

    // check if (0, 4) are in the same set and (3, 5) are not
    Iitem ref0, ref4;
    if (!uf.FindSet(items[0], ref0))
    {
	    throw std::runtime_error("item0 not in set");
    }
    if(!uf.FindSet(items[4], ref4))
    {
	    throw std::runtime_error("item4 not in set");
    }

    assert(ref0 == ref4);

    Iitem ref3, ref5;
    if (!uf.FindSet(items[3], ref3))
    {
	    throw std::runtime_error("item3 not in set");
    }
    if (!uf.FindSet(items[5], ref5))
    {
	    throw std::runtime_error("item5 not in set");
    }
    assert(ref3 != ref5);
    std::cout << "Success!" << std::endl;
}


void TestMorrisTraversal()
{

    // create test tree (1, 2, 3, 4, 5, 6, 7)
    std::unique_ptr<Node<int> > root = std::make_unique<Node<int> >(4);
    std::unique_ptr<Node<int> > node1 = std::make_unique<Node<int> >(1);
    std::unique_ptr<Node<int> > node2 = std::make_unique<Node<int> >(2);
    std::unique_ptr<Node<int> > node3 = std::make_unique<Node<int> >(3);
    std::unique_ptr<Node<int> > node5 = std::make_unique<Node<int> >(5);
    std::unique_ptr<Node<int> > node6 = std::make_unique<Node<int> >(6);
    std::unique_ptr<Node<int> > node7 = std::make_unique<Node<int> >(7);
    

    node2->left_ = std::move(node1);
    node2->right_ = std::move(node3);

    node6->left_ = std::move(node5);
    node6->right_ = std::move(node7);

    root->left_ = std::move(node2);
    root->right_ = std::move(node6);

    Tree<int> tree(std::move(root));

    auto results = tree.MorrisTraversal();
    for (auto const& res : results)
    {
        std::cout << res << " ";
    }
    std::cout << std::endl;
    
}

void TestStringUtils()
{
    std::string str = "fsgbbfg, rsgfrg, adsgvdsbvf , wqrgvsfrb,  qwvfb,  wb frb  , rwf df , fvfsgvbfsbsbfb dfb  f , frgvfsb fbb , frswbfsb  ,thysaeafv ,354vrgvv ,dsbv fs ,sdf fsv sdfvsdvsdv,ads dfsvdsvdsvds, ds sdv ,dasgdbva";
    auto r1 = StringUtils::Split1(str);
    auto r2 = StringUtils::Split2(str);

    assert(r1.size() == r2.size());
}



std::vector<std::pair<std::string, int> > GenerateInputs()
{
    std::vector<std::pair<std::string, int> > v;
    std::string str = "test";
    
    for (int i = 0 ; i < 50000; ++i)
    {
        std::stringstream ss;
        ss << i;
        v.emplace_back(str + ss.str(), i);
        ss.clear();
    }
    return std::move(v);
}


HashTable<std::string, int> table;
// std::unordered_map<std::string, int> table;


void TesthashTable(std::vector<std::pair<std::string, int> > const& input)
{
   

    for(auto const& kvp : input)
    {
        table.Insert(kvp.first, kvp.second);
    }
}


// void TestUnorderedMap(std::vector<std::pair<std::string, int> > const& input)
// {
   
//     for(auto const& kvp : input)
//     {
//         table.emplace(kvp.first, kvp.second);
//     }
// }


static void TestThreadSafeQueue_ManyProducersOneConsumer()
{
    ThreadSafeQueue<std::string> q;
    auto consumer = std::thread([&q](){
        for (int i = 0; i < 7; ++i)
        {
            std::string item;
            q.Dequeue(item);
            std::cout << item << std::endl;
        }
    });

    auto producer0 = std::thread([&q](){
        q.Enqueue("test0_prod0");
        q.Enqueue("test1_prod0");
        q.Enqueue("test2_prod0");
        q.Enqueue("test3_prod0");
    });

    std::vector<std::string> strs = {"test0_prod1", "test1_prod1", "test2_prod1"};
    auto producer1 = std::thread([&q, &strs](){
        for (auto const& val : strs)
        {
            q.Enqueue(val);
        }
    });

    producer1.join();
    producer0.join();
    consumer.join();
}

static void TestThreadPoolQueue_ManyProducersOneConsumer()
{
    ThreadPoolQueue<std::string> q;
    auto consumer = std::thread([&q](){
        for (int i = 0; i < 7; ++i)
        {
            std::string item;
            q.Dequeue(item);
            std::cout << item << std::endl;
        }
    });

    auto producer0 = std::thread([&q](){
        q.Enqueue("test0_prod0");
        q.Enqueue("test1_prod0");
        q.Enqueue("test2_prod0");
        q.Enqueue("test3_prod0");
    });

    std::vector<std::string> strs = {"test0_prod1", "test1_prod1", "test2_prod1"};
    auto producer1 = std::thread([&q, &strs](){
        for (auto const& val : strs)
        {
            q.Enqueue(val);
        }
    });

    producer1.join();
    producer0.join();
    consumer.join();
}

static void TestThreadPoolQueue_IdleConsumersRelease()
{
    ThreadPoolQueue<std::string> q;
    auto consumer0 = std::thread([&q](){
        for (int i = 0; i < 7; ++i)
        {
            std::string item = "";
            q.Dequeue(item);
            std::cout << item << std::endl;
        }
    });

    auto consumer1 = std::thread([&q](){
        for (int i = 0; i < 7; ++i)
        {
            std::string item;
            q.Dequeue(item);
            std::cout << item << std::endl;
        }  
   });

    q.ReleaseThreads();
    consumer0.join();
    consumer1.join();
}

static void TestInsertAndRetrieve()
{
    ThreadSafeQueue<int> q;
    auto consumer = std::thread([&q](){
        for (int i = 0; i < 100; ++i)
        {
            int item;
            q.Dequeue(item);
            std::cout << item << std::endl;
        }
    });

    auto producer = std::thread([&q](){
        for (int i = 0; i < 100; ++i)
        {
            q.Enqueue(i);
        }
    });

    producer.join();
    consumer.join();
}


static void TestThreadPool_BasicTest()
{
    std::vector<int> val {1234, 0, 0, 0};

    ThreadPool<ThreadContext> threadPool;

    threadPool.AddJob(std::move(ThreadContext(val.data(), 10)));
    threadPool.AddJob(ThreadContext(&val[1], 20));
    threadPool.AddJob(ThreadContext(&val[2], 30));
    threadPool.AddJob(ThreadContext(&val[3], 40));


    // sleep for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

//    threadPool.KillAllThreads();
    threadPool.Join();


    for (auto const& v : val)
    {
	std::cout << v << std::endl;
    }
}

int main(int argc, char **argv)
{
    // auto input = GenerateInputs();
    // auto start = std::chrono::high_resolution_clock::now(); 
    // TesthashTable(input);
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // std::cout << "Time in milliseconds for inserting 50000 inputs " <<  duration.count() << std::endl;

    //TestThreadSafeQueue_ManyProducersOneConsumer();
    //TestThreadPoolQueue_ManyProducersOneConsumer();
    //TestThreadPoolQueue_IdleConsumersRelease();
    TestThreadPool_BasicTest();
    return 0;
}

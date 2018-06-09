#pragma once

#include<vector>
#include<semaphore.h>
namespace server{
    template<typename T>
    class BlockQueue{
    public:
        BlockQueue(size_t s=1024):data_(s),head_(0),tail_(0),size_(0){
            sem_init(&sem_data_,0,0);//full
            sem_init(&sem_black_,0,s);//empty
        }
        void PushBack(const T& value){
            sem_wait(&sem_black_);
            data_[tail_++] = value;
            if(tail_>data_.size())
            {
                tail_=0;
            }
            ++size_;
            sem_post(&sem_data_);
        }
        void PopBack(T* value){
            sem_wait(&sem_data_);
            *value = data_[head_++];
            if(head_>data_.size())
            {
                head_=0;
            }
            sem_post(&sem_black_);
        }

        void PopFront(T* value){
            sem_wait(&sem_data_);
            *value =data_[head_++];
            if(head_>data_.size()){
                head_=0;
            }
            --size_;
        }

        ~BlockQueue()
        {
            sem_destroy(sem_data_);
            sem_destroy(sem_black_);
        }
    private:
        std::vector<T> data_;
        //由于实现的是单生产者但消费者
        //可以不加互斥锁
        sem_t sem_data_;
        sem_t sem_black_;
        //sem_t sem_lock_;
        size_t head_;
        size_t tail_;
        size_t size_;
    };//end BlockQueue
}//end pair


#include "QueueTests.h"
#include <iostream>
#include <thread>


/*Lock Free Queues
Public domain implementation of four different lock free queues:

SPSC lock free dynamic queue which requires a memory allocation with each insert.
MPSC lock free dynamic queue which requires a memory allocation with each insert.
SPSC wait free bound queue/ring buffer which which uses a fixed size pre-allocated buffer.
MPMC lock free bound queue/ring buffer which which uses a fixed size pre-allocated buffer.
Performance

These number are on my Early 2013 Retina Macbook Pro (2.7 GHz i7). The latency variability of memory allocation can have a signifigant impact on the dynamic queues, sometimes halving throughput.

Queue	Throughput
SPSC dynamic	8 million
MPSC dynamic	8 million
SPSC fixed	200 million
MPMC fixed	54 million
*/

CPPUNIT_TEST_SUITE_REGISTRATION( QueueTests );

QueueTests::QueueTests(){


}

QueueTests::~QueueTests(){


}
/*

#define COUNT 100
//#define COUNT 100000000

template<typename T>
void
consumer_func(
		T* queue)
{
	size_t count = COUNT;
	size_t value = 0;

	while (count > 0) {
		if (queue->dequeue(value)) {
			--count;
		}
	}
}

template<typename T>
void
bounded_producer_func(
		T* queue)
{
	size_t count = COUNT;
	while (count > 0) {
		if (queue->enqueue(count)) {
			--count;
		}
	}
}

template<typename T>
void
producer_func(
		T* queue)
{
	for (int count = 0; count < COUNT; ++count) {
		queue->enqueue(count);
	}
}

template<typename T>
long double
run_test(
		T producer_func,
		T consumer_func)
{
	typedef std::chrono::high_resolution_clock clock_t;
	typedef std::chrono::time_point<clock_t> time_t;
	time_t start;
	time_t end;

	start = clock_t::now();
	boost::thread producer(producer_func);
	boost::thread consumer(consumer_func);

	producer.join();
	consumer.join();
	end = clock_t::now();

	return
			(end - start).count()
			* ((double) std::chrono::high_resolution_clock::period::num
					/ std::chrono::high_resolution_clock::period::den);
}
*/
void QueueTests::test(){
	/*
	{
		typedef spsc_bounded_queue_t<size_t> queue_t;
		queue_t queue(65536);
		long double seconds = run_test(std::bind(&bounded_producer_func<queue_t>, &queue),
				std::bind(&consumer_func<queue_t>, &queue));



	        std::cout << "SPSC bound queue completed "
	                  << COUNT
	                  << " iterations in "
	                  << seconds
	                  << " seconds. "
	                  << ((long double) COUNT / seconds) / 1000000
	                  << " million enqueue/dequeue pairs per second."
	                  << std::endl;
	}

	{
		typedef mpmc_bounded_queue_t<size_t> queue_t;
		queue_t queue(65536);
		long double seconds = run_test(std::bind(&bounded_producer_func<queue_t>, &queue),
				std::bind(&consumer_func<queue_t>, &queue));

	        std::cout << "MPMC bound queue completed "
	                  << COUNT
	                  << " iterations in "
	                  << seconds
	                  << " seconds. "
	                  << ((long double) COUNT / seconds) / 1000000
	                  << " million enqueue/dequeue pairs per second."
	                  << std::endl;
	}

	{
		typedef spsc_queue_t<size_t> queue_t;
		queue_t queue;
		long double seconds = run_test(std::bind(&producer_func<queue_t>, &queue),
				std::bind(&consumer_func<queue_t>, &queue));

	        std::cout << "SPSC dynamic queue completed "
	                  << COUNT
	                  << " iterations in "
	                  << seconds
	                  << " seconds. "
	                  << ((long double) COUNT / seconds) / 1000000
	                  << " million enqueue/dequeue pairs per second."
	                  << std::endl;
	}

	{
		typedef mpsc_queue_t<size_t> queue_t;
		queue_t queue;
		long double seconds = run_test(std::bind(&producer_func<queue_t>, &queue),
				std::bind(&consumer_func<queue_t>, &queue));

	        std::cout << "MPSC dynamic queue completed "
	                  << COUNT
	                  << " iterations in "
	                  << seconds
	                  << " seconds. "
	                  << ((long double) COUNT / seconds) / 1000000
	                  << " million enqueue/dequeue pairs per second."
	                  << std::endl;
	}

	{
		typedef mpsc_queue_t<int> queue_t;
		queue_t queue;
		queue.enqueue(5);
		int value;
		queue.dequeue(value);
		CPPUNIT_ASSERT(value == 5);
	}

*/

}

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;

 /* Realizing in making a priority queue that each thread would be manipulating
     multiple variables, initially I wanted to make a class but after
     investigating I made two structs using
     https://www.geeksforgeeks.org/stl-priority-queue-for-structure-or-class/ as
     reference In order to make an STL priority queue
  */
struct Thread {
    //sets up the
		int thread_number;
    long long next_free_time = 0;
	    Thread (int thread_number):thread_number(thread_number){}
};
//thread compare is needed for the priority queue to run in the first place. 
//in this case, priority is dictated by the next time available, all variables start at 0
struct ThreadCompare {
	bool operator()(const Thread &t1, const Thread &t2) const {
    //in cases where they're all the same time to execute min threads (0>1>2>3 etc.) 
    //take priority
		if(t1.next_free_time == t2.next_free_time)
			return t1.thread_number > t2.thread_number;
    //otherwise it goes off which one is free sooner
		else
      return t1.next_free_time > t2.next_free_time;
	}
};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
	assigned_workers_.resize(jobs_.size());
  start_times_.resize(jobs_.size());
    //create a priority queue 
	priority_queue<Thread, vector<Thread>, ThreadCompare> pq;
	for(int i = 0; i < num_workers_; i++) {
    //fill up priority queue with designated threads 
		pq.push(Thread(i));

	}
  //for each thread using the struct assigned earlier, we add the next working thread and pop
  //it to the stack, 
    
	for (int i = 0; i < jobs_.size(); i++) {
    //Sets up the next thread and the duration of the job it is given before adding it into the
    //array of assigned workers, using 
    int duration = jobs_[i];
		Thread next_worker = pq.top();
		pq.pop();
    //adds current thread to the growing array of working threads, using it's # in the queue
		assigned_workers_[i] = next_worker.thread_number;
    //establishes the next time it starts using the thread's free time 
		start_times_[i] = next_worker.next_free_time;
    //increments the thread's free time based on the current job's duration 
		next_worker.next_free_time += duration;
    //adds the next worker to the queue 
		pq.push(next_worker);
	} 
  }
  
 public:
  void Solve() {
    ReadData();
	  AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
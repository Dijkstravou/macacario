deque<int> q;

int minimum = q.front();

// Add
while (!q.empty() && q.back() > new_element)
    q.pop_back();
q.push_back(new_element);

// Remove
if (!q.empty() && q.front() == remove_element) q.pop_front();
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

int main() {
    string line;
    
    // Read "Frames" and the number of frames
    int numFrames;
    cin >> line >> numFrames;
    
    // Read the reference string
    getline(cin, line); // consume newline
    getline(cin, line); // read the actual reference string
    
    // Parse the reference string
    vector<int> references;
    stringstream ss(line);
    int page;
    while (ss >> page) {
        references.push_back(page);
    }
    
    // Output the reference string
    for (int i = 0; i < references.size(); i++) {
        cout << references[i];
        if (i < references.size() - 1) cout << " ";
    }
    cout << endl;
    
    cout << "Page replacement using LRU" << endl;
    
    // LRU implementation
    vector<int> frames;        // stores current pages in frames
    vector<int> lastUsed;      // tracks when each frame was last used
    int pageFaults = 0;
    
    for (int t = 0; t < references.size(); t++) {
        int currentPage = references[t];
        
        // Check if page is already in frames
        int frameIndex = -1;
        for (int i = 0; i < frames.size(); i++) {
            if (frames[i] == currentPage) {
                frameIndex = i;
                break;
            }
        }
        
        if (frameIndex != -1) {
            // Page hit - update last used time for this frame
            lastUsed[frameIndex] = t;
        } else {
            // Page fault
            pageFaults++;
            
            if (frames.size() < numFrames) {
                // Still have empty frames available
                frames.push_back(currentPage);
                lastUsed.push_back(t);
            } else {
                // All frames are full - need to replace the LRU page
                // Find the frame with the smallest lastUsed time (least recently used)
                int lruIndex = 0;
                for (int i = 1; i < lastUsed.size(); i++) {
                    if (lastUsed[i] < lastUsed[lruIndex]) {
                        lruIndex = i;
                    }
                }
                // Replace the LRU frame
                frames[lruIndex] = currentPage;
                lastUsed[lruIndex] = t;
            }
        }
        
        // Output current state of frames
        cout << "time step " << t << ": ";
        for (int i = 0; i < frames.size(); i++) {
            cout << frames[i];
            if (i < frames.size() - 1) cout << " ";
        }
        cout << endl;
    }
    
    cout << "total number of page faults = " << pageFaults << endl;
    
    return 0;
}

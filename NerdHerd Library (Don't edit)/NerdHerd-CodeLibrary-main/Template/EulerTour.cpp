vector<multiset<int> >adj; vector<int>ans;
void euler_circuit(int src){
 stack<int>st; st.push(src);
 while(!st.empty()){
  int v = st.top();
  if(adj[v].size()==0){
   ans.push_back(v); st.pop();
  }
  else{
   int f = *adj[v].begin();
   adj[v].erase(adj[v].begin()); adj[f].erase(adj[f].find(v));
   st.push(f);
  }
 }
}

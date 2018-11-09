Let disc_time[v] = -1 and explored[v] = false forall v
dfscounter = 0

DFS(v):
  explored[v] = true
  disc_time[v] = low[v] = ++dfscounter
  foreach edge (v,x):
    if !explored[x]:
      DFS(x)
      low[v] = min(low[v], low[x])
      if low[x] >= disc_time[v]:
        print “v is articulation point separating x”
    elif x is not v’s parent:
      low[v] = min(low[v], disc_time[x])

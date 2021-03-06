import pyOcean_cpu as ocean

A = ocean.arange(2*3*4,ocean.float).reshape([2,3,4])
print(A)

print(ocean.norm2(A,[0,1]))

A.fliplr(True)
print(ocean.minimum(A,0))
print(ocean.maximum(A,2,True))

B = ocean.tensor([4],ocean.half)
ocean.norm(A,3,[0,1],B)
print(B)
print(ocean.norm(A,3,[0,1]))

using MLDatasets.MNIST
using LinearAlgebra

# load full training set
train_vec, train_label = traindata(Float32)

# load full test set
test_vec,  test_label  = testdata(Float32)

K = 3
numOfErrors = 0

for i in 1:size(test_vec)[3]
    kClosets = zeros(K, 2)
    for j in 1:K
        kClosets[j,1] = 10 ^ 8
        kClosets[j,2] = -1
    end

    for j in 1:size(train_vec)[3]
        distance = norm( test_vec[:,:,i] - train_vec[:,:,j] )

        max = -1
        pos = -1
        for l in 1:K
            if kClosets[l,1] > max
                max = kClosets[l,1]
                pos = l
            end
        end

        if distance < max
            kClosets[pos,1] = distance
            kClosets[pos,2] = train_label[j]
        end

    end

    digits = zeros(10)
    max = -1
    predicted = -1
    for j in 1:K
        digits[ trunc(Int, kClosets[j,2] + 1) ] += 1

        if digits[ trunc(Int, kClosets[j,2] + 1) ] >= max
            max = digits[ trunc(Int, kClosets[j,2] + 1) ]
            predicted = kClosets[j,2]
        end
    end

    if test_label[i] != predicted
        global numOfErrors += 1
    end

    #print(numOfErrors, "\n")
    print("%" , 100 * numOfErrors / size(test_vec)[3], "\n")

end

print("%" , 100 * numOfErrors / size(test_vec)[3], "\n")
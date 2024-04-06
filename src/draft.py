"""
Consider the problem of determining if a text was rewritten by ChatGPT. The idea is to build a
program that, for a certain target text that is given to it, t, it indicates one of two possibilities:
(1) the text was not rewritten by ChatGPT; (2) the text was rewritten by ChatGPT.
Usually, the traditional approach to solve this classification problem begins with feature extrac-
tion and selection operations. The features obtained are then fed into a function that maps
the feature space onto the set of classes and performs the classification. One of the most dif-
ficult parts of this problem is how to choose the smallest set of features that retains enough
discriminant power to tackle the problem.

The idea is the following. For each class (in this case, we have only two), represented by a
reference text ri, we create a model that is a good description of ri. By a “good description”
we mean a model that requires fewer bits to describe ri than other models, or, in other words,
that is a good compression model for the “members of the class” ri. Then, we assign to t the
class corresponding to the model that requires fewer bits to describe it, i.e., to compress t.
01

FCM will be a Markov model
"""

k = 2 # window size

txt = "ABBAABABBB" # imaginar AA antes

alphabet = "AB"

from itertools import product
d = {"".join(p): {c : 0 for c in alphabet} for p in product(alphabet, repeat=k)}
print(d)

pos = k # TODO: pos = 0 e imaginar AA antes
current = txt[pos-k:pos] #AB

while pos < len(txt):
    next_char = txt[pos]
    d[current][next_char] += 1
    current = current[1:] + next_char
    pos += 1

print(d)


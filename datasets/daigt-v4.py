import pandas as pd
import numpy as np
import os

os.makedirs("out/daigt", exist_ok=True)
os.makedirs("out/daigt/train", exist_ok=True)
os.makedirs("out/daigt/val", exist_ok=True)

os.makedirs("out/daigt/train/0", exist_ok=True)
os.makedirs("out/daigt/train/1", exist_ok=True)
os.makedirs("out/daigt/val/0", exist_ok=True)
os.makedirs("out/daigt/val/1", exist_ok=True)

df = pd.read_csv("raw/train_v4_drcat_01.csv")
df_0 = df[df["label"] == 0]
df_1 = df[df["label"] == 1]


min_samples = min(df_0.shape[0], df_1.shape[0])
df_0 = df_0.iloc[:min_samples]
df_1 = df_1.iloc[:min_samples]

for type, data in {"0": df_0["text"], "1": df_1["text"]}.items():
    # data = data.str.lower()
    data = data.str.replace("\n", " ")

    train_size = int(0.8 * min_samples)
    train_df, test_df = data.iloc[:train_size], data.iloc[train_size:]
    np.savetxt(f"out/daigt/test{type}.txt", test_df.values, fmt="%s")

    # create kfold splits
    splits = np.array_split(train_df.values, 10)

    # iterate over splits, choose 1 split for validation, rest for training
    for i, split in enumerate(splits):
        train_folds = np.concatenate([splits[j] for j in range(10) if j != i])
        np.savetxt(f"out/daigt/train/{type}/train{i}.txt", train_folds, fmt="%s")
        np.savetxt(f"out/daigt/val/{type}/val{i}.txt", split, fmt="%s")

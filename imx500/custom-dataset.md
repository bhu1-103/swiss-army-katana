# Train a yolo model on your own dataset

## Source the dataset

### You can download a dataset from websites like roboflow

- Go to [roboflow](https://universe.roboflow.com/search?q=) and select any dataset you like

- The dataset can either be downladed as a zip file or you can install the roboflow library and import a dataset directly from the python library

### You can get your own images and arrange them in a folder

- Make a folder called **dataset-01**

```bash
mkdir dataset-01
cd dataset-01
```

- Make 3 folders called **train**, **test** and **valid**. Also create a file called **data.yaml**

```bash
mkdir train
mkdir test
mkdir valid

touch data.yaml
```
- Inside each of the folders, make 2 folders each, **images** and **labels**

```bash
for f in train test valid; do
    mkdir -p "$f/images" "$f/labels"
done
```

- Now, add your images and labels here

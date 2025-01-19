1. According to your python version, run  "python3 -m venv venv" or "python -m venv venv"

2. Run: "source venv/bin/activate"

3. Run "pip install numpy pillow matplotlib" if they have not already been installed.

4. Run "python3 main.py <dataset_dir_PCA> <dataset_dir_LR>", where <dataset_dir_PCA> is the path of the directory where the dataset for the PCA question (first question) is residing on your computer and <dataset_dir_LR> is the path of the directory where the mnist dataset for the logistic regression question (second question) is residing on your computer. For example, in my case, it was '/Users/yaseminakin/Desktop/resized_images'.

5. Then, the answers to the questions are directly printed in the main() in a very clear format. The plots can either be viewed from the plot viewing section of your specific IDE (SciView section in VSCode Jupyter Notebook Environment) or from the report.

6. Deactivate virtual environment when done with "deactivate" command.
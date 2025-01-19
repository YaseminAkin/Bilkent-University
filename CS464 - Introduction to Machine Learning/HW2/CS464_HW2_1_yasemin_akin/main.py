import numpy as np
import os
from PIL import Image
import matplotlib.pyplot as plt
import sys


# QUESTION 1

def pca(flattened_channel_matrix):
    centered_channel = flattened_channel_matrix - np.mean(flattened_channel_matrix, axis=0)
    covariance_matrix = np.cov(centered_channel, rowvar=False)
    eigenvalues, eigenvectors = np.linalg.eig(covariance_matrix)

    sorted_indices = np.argsort(eigenvalues)[::-1]
    eigenvalues = eigenvalues[sorted_indices]
    eigenvectors = eigenvectors[:, sorted_indices]

    total_variance = np.sum(eigenvalues)
    pve = eigenvalues / total_variance

    top_10_eigenvectors = eigenvectors[:, :10]
    top_10_pve = pve[:10]

    cumulative_pve = np.cumsum(pve)
    min_components = np.argmax(cumulative_pve >= 0.7) + 1

    return top_10_eigenvectors, top_10_pve, pve, min_components


def question1_2(eigenvectors_R, eigenvectors_G, eigenvectors_B):
    rgb_images = []

    for i in range(10):
        pc_R = eigenvectors_R[:, i].reshape(64, 64)
        pc_G = eigenvectors_G[:, i].reshape(64, 64)
        pc_B = eigenvectors_B[:, i].reshape(64, 64)

        min_val = np.min(pc_R)
        max_val = np.max(pc_R)
        scaled_pc_R = (pc_R - min_val) / (max_val - min_val)

        min_val = np.min(pc_G)
        max_val = np.max(pc_G)
        scaled_pc_G = (pc_G - min_val) / (max_val - min_val)

        min_val = np.min(pc_B)
        max_val = np.max(pc_B)
        scaled_pc_B = (pc_B - min_val) / (max_val - min_val)

        rgb_image = np.stack([scaled_pc_R, scaled_pc_G, scaled_pc_B], axis=-1)
        rgb_images.append(rgb_image)

    plt.figure(figsize=(15, 6))
    for i, img in enumerate(rgb_images):
        plt.subplot(2, 5, i + 1)
        plt.imshow(img)
        plt.title(f"PC {i + 1}")
        plt.axis('off')
    plt.show()


def question1_3(X, k, index_reconstruct):
    reconstructed_channels = []

    for c in range(3):
        X_c = X[:, :, c]

        mean_X_c = np.mean(X_c, axis=0)
        centered_X_c = X_c - mean_X_c
        covariance_matrix = np.cov(centered_X_c, rowvar=False)

        eigenvalues, eigenvectors = np.linalg.eigh(covariance_matrix)
        sorted_indices = np.argsort(eigenvalues)[::-1]
        eigenvalues = eigenvalues[sorted_indices]
        eigenvectors = eigenvectors[:, sorted_indices]

        top_k_eigenvectors = eigenvectors[:, :k]
        centered_image_c = centered_X_c[index_reconstruct]
        coefficients = np.dot(centered_image_c, top_k_eigenvectors)
        reconstructed_centered = np.dot(coefficients, top_k_eigenvectors.T)
        reconstructed_channel = reconstructed_centered + mean_X_c

        reconstructed_channel = reconstructed_channel.reshape(64, 64)

        reconstructed_channels.append(reconstructed_channel)

    reconstructed_image = np.stack(reconstructed_channels, axis=-1) 

    reconstructed_image = np.clip(reconstructed_image, 0, 255).astype(np.uint8)

    return reconstructed_image


# QUESTION 2
# Function for one-hot encoding
def one_hot_encoding(label_data):
    row_number = label_data.shape[0]
    num_labels = 10  # MNIST dataset (0-9)
    encoded_labels = np.zeros((row_number, num_labels), dtype='int')
    encoded_labels[list(range(row_number)), label_data] = 1
    return encoded_labels


# Function to read pixel data from the dataset
def read_pixels(data_path):
    with open(data_path, 'rb') as f:
        pixel_data = np.frombuffer(f.read(), 'B', offset=16).astype('float32')
    flattened_pixels = pixel_data.reshape(-1, 784)
    normalized_pixels = flattened_pixels / 255
    return normalized_pixels


# Function to read label data from the dataset
def read_labels(data_path):
    with open(data_path, 'rb') as f:
        label_data = np.frombuffer(f.read(), 'B', offset=8)
    one_hot_encoding_labels = one_hot_encoding(label_data)
    return one_hot_encoding_labels


# Function to read the entire dataset
def read_dataset(path):
    X_train = read_pixels(path + "/train-images-idx3-ubyte")
    y_train = read_labels(path + "/train-labels-idx1-ubyte")
    X_test = read_pixels(path + "/t10k-images-idx3-ubyte")
    y_test = read_labels(path + "/t10k-labels-idx1-ubyte")
    return X_train, y_train, X_test, y_test


def softmax(scores):
    scores_exp = np.exp(scores)
    denominator = scores_exp.sum(1, keepdims=True)
    return scores_exp / denominator


def compute_loss(y_pred, y_true, weights, reg_coeff):
    N = y_true.shape[0]
    cross_entropy = -np.sum(y_true * np.log(y_pred)) / N

    l2_reg = (reg_coeff / 2) * np.sum(weights ** 2)
    loss = cross_entropy + l2_reg

    return loss


def initialize_weights(input_dim, num_classes, init_type="normal"):
    if init_type == "zero":
        return np.zeros((input_dim, num_classes))
    elif init_type == "uniform":
        return np.random.uniform(-0.1, 0.1, (input_dim, num_classes))
    elif init_type == "normal":
        return np.random.normal(0, 1, (input_dim, num_classes))
    else:
        raise ValueError("Invalid initialization type. Choose from 'zero', 'uniform', or 'normal'.")


def compute_confusion_matrix(y_true, y_pred, num_classes):
    matrix = np.zeros((num_classes, num_classes), dtype=int)
    for true, pred in zip(y_true, y_pred):
        matrix[true, pred] += 1
    return matrix


def train_and_evaluate(X_train, y_train, X_val, y_val, X_test, y_test, num_classes,
                       batch_size=200, learning_rate=5e-4, reg_coeff=1e-4,
                       init_type="normal", epochs=100):
    num_samples, input_dim = X_train.shape
    weights = initialize_weights(input_dim, num_classes, init_type)
    b = np.zeros((num_classes))

    val_losses, val_accuracies = [], []

    for _ in range(epochs):
        indices = np.arange(num_samples)
        np.random.shuffle(indices)
        X_train, y_train = X_train[indices], y_train[indices]

        for i in range(0, num_samples, batch_size):
            X_batch = X_train[i:i + batch_size]
            y_batch = y_train[i:i + batch_size]

            z = np.dot(X_batch, weights) + b
            y_pred = softmax(z)
            loss = compute_loss(y_pred, y_batch, weights, reg_coeff)
            dw = np.dot(X_batch.T, y_pred - y_batch) + reg_coeff * weights
            dw0 = np.sum(y_pred - y_batch) 
            weights -= learning_rate * dw
            b -= learning_rate * dw0

        logits_val = np.dot(X_val, weights) + b
        y_pred_val = softmax(logits_val)
        val_loss = -np.sum(y_val * np.log(y_pred_val + 1e-15)) / y_val.shape[0]
        val_accuracy = np.mean(np.argmax(y_pred_val, axis=1) == np.argmax(y_val, axis=1))

        val_losses.append(val_loss)
        val_accuracies.append(val_accuracy)

    logits_test = np.dot(X_test, weights) + b
    y_pred_test = softmax(logits_test)
    test_accuracy = np.mean(np.argmax(y_pred_test, axis=1) == np.argmax(y_test, axis=1))

    y_test_labels = np.argmax(y_test, axis=1)
    y_pred_test_labels = np.argmax(y_pred_test, axis=1)
    conf_matrix = compute_confusion_matrix(y_test_labels, y_pred_test_labels, num_classes)

    metrics = {
        "val_losses": val_losses,
        "val_accuracies": val_accuracies,
        "test_accuracy": test_accuracy,
        "confusion_matrix": conf_matrix
    }

    return weights, metrics


def run_experiments(X_train, y_train, X_val, y_val, X_test, y_test, num_classes, epochs=100):
    results = {}

    default_params = {
        "batch_size": 200,
        "learning_rate": 5e-4,
        "reg_coeff": 1e-4,
        "init_type": "normal"
    }

    # 1. Experiment with Batch Sizes
    batch_sizes = [1, 64, 3000]
    for batch_size in batch_sizes:
        print(f"Experimenting with Batch Size: {batch_size}")
        weights, metrics = train_and_evaluate(
            X_train, y_train, X_val, y_val, X_test, y_test,
            num_classes, batch_size=batch_size,
            learning_rate=default_params["learning_rate"],
            reg_coeff=default_params["reg_coeff"],
            init_type=default_params["init_type"], epochs=epochs
        )
        results[f"batch_size_{batch_size}"] = metrics

    # 2. Experiment with Weight Initialization
    init_types = ["zero", "uniform", "normal"]
    for init_type in init_types:
        print(f"Experimenting with Weight Initialization: {init_type}")
        weights, metrics = train_and_evaluate(
            X_train, y_train, X_val, y_val, X_test, y_test,
            num_classes, batch_size=default_params["batch_size"],
            learning_rate=default_params["learning_rate"],
            reg_coeff=default_params["reg_coeff"],
            init_type=init_type, epochs=epochs
        )
        results[f"init_type_{init_type}"] = metrics

    # 3. Experiment with Learning Rates
    learning_rates = [0.01, 1e-3, 1e-4, 1e-5]
    for learning_rate in learning_rates:
        print(f"Experimenting with Learning Rate: {learning_rate}")
        weights, metrics = train_and_evaluate(
            X_train, y_train, X_val, y_val, X_test, y_test,
            num_classes, batch_size=default_params["batch_size"],
            learning_rate=learning_rate,
            reg_coeff=default_params["reg_coeff"],
            init_type=default_params["init_type"], epochs=epochs
        )
        results[f"learning_rate_{learning_rate}"] = metrics

    # 4. Experiment with Regularization Coefficients
    reg_coeffs = [1e-2, 1e-4, 1e-9]
    for reg_coeff in reg_coeffs:
        print(f"Experimenting with Regularization Coefficient: {reg_coeff}")
        weights, metrics = train_and_evaluate(
            X_train, y_train, X_val, y_val, X_test, y_test,
            num_classes, batch_size=default_params["batch_size"],
            learning_rate=default_params["learning_rate"],
            reg_coeff=reg_coeff,
            init_type=default_params["init_type"], epochs=epochs
        )
        results[f"reg_coeff_{reg_coeff}"] = metrics

    return results


def plot_validation_accuracy(results, hyperparameter_name, title):
    plt.figure(figsize=(10, 6))

    for key, metrics in results.items():
        if hyperparameter_name in key:
            label = key.split('_')[-1]
            epochs = list(range(1, len(metrics["val_accuracies"]) + 1))
            accuracies = metrics["val_accuracies"]
            plt.plot(epochs, accuracies, label=f"{hyperparameter_name.capitalize()}: {label}")

    plt.title(title)
    plt.xlabel("Epochs")
    plt.ylabel("Validation Accuracy")
    plt.legend()
    plt.grid(True)
    plt.show()


def visualize_weights(weights, class_names=None):
    num_classes = weights.shape[1]
    plt.figure(figsize=(10, 8))

    for i in range(num_classes):
        weight_image = weights[:, i].reshape(28, 28)  
        weight_image = (weight_image - weight_image.min()) / (
                weight_image.max() - weight_image.min())  
        weight_image = (weight_image * 255).astype(np.uint8)

        plt.subplot(2, 5, i + 1)
        plt.imshow(weight_image, cmap='gray')
        title = f"Class {i}" if class_names is None else class_names[i]
        plt.title(title)
        plt.axis('off')

    plt.suptitle("Visualization of Weight Vectors")
    plt.show()


def compute_metrics(conf_matrix):
    num_classes = conf_matrix.shape[0]
    metrics = {"precision": [], "recall": [], "f1": [], "f2": []}

    for k in range(num_classes):
        true_positive = conf_matrix[k, k]
        false_positive = conf_matrix[:, k].sum() - true_positive
        false_negative = conf_matrix[k, :].sum() - true_positive

        precision = true_positive / (true_positive + false_positive + 1e-15)
        recall = true_positive / (true_positive + false_negative + 1e-15)
        f1 = 2 * (precision * recall) / (precision + recall + 1e-15)
        f2 = 5 * (precision * recall) / (4 * precision + recall + 1e-15)

        metrics["precision"].append(precision)
        metrics["recall"].append(recall)
        metrics["f1"].append(f1)
        metrics["f2"].append(f2)

    return metrics


def print_metrics(metrics, class_names=None):
    num_classes = len(metrics["precision"])
    for k in range(num_classes):
        class_label = f"Class {k}" if class_names is None else class_names[k]
        print(f"{class_label}:")
        print(f"  Precision: {metrics['precision'][k]:.4f}")
        print(f"  Recall: {metrics['recall'][k]:.4f}")
        print(f"  F1 Score: {metrics['f1'][k]:.4f}")
        print(f"  F2 Score: {metrics['f2'][k]:.4f}")
        print()


def main():
    # QUESTION 1 MAIN
    
    img_dir = sys.argv[1]
    imgs = []
    file_names = os.listdir(img_dir)
    index = 0
    img_reconstruct = 0
    index_reconstruct = 0
    for file_name in file_names:
        file_path = os.path.join(img_dir, file_name)

        try:
            img = Image.open(file_path)
            if file_name == "image_9577.png":
                img_reconstruct = img
                index_reconstruct = index
            img = np.array(img).astype(np.float32)
            flattened_img = img.reshape(-1, 3)
            imgs.append(flattened_img)
        except Exception as e:
            print(f"Could not open file {file_path}: {e}")
        index += 1

    X = np.stack(imgs, axis=0)
    X_R = X[:, :, 0]
    X_G = X[:, :, 1]
    X_B = X[:, :, 2]

    print("----------Question 1.1----------")
    top_10_eigenvectors_R, top_10_pve_R, pve_R, min_components_R = pca(X_R)
    top_10_eigenvectors_G, top_10_pve_G, pve_G, min_components_G = pca(X_G)
    top_10_eigenvectors_B, top_10_pve_B, pve_B, min_components_B = pca(X_B)

    print("PVEs of top 10 principal components for red channel:", top_10_pve_R)
    print("Sum of PVEs of top 10 principal components for red channel:", np.sum(top_10_pve_R))
    print(f"Minimum components for 70% PVE for red channel: {min_components_R}")

    print("PVEs of top 10 principal components for green channel:", top_10_pve_G)
    print("Sum of PVEs of top 10 principal components for green channel:", np.sum(top_10_pve_G))
    print(f"Minimum components for 70% PVE for green channel: {min_components_G}")

    print("PVEs of top 10 principal components for blue channel:", top_10_pve_B)
    print("Sum of PVEs of top 10 principal components for blue channel", np.sum(top_10_pve_B))
    print(f"Minimum components for 70% PVE for blue channel: {min_components_B}")

    print("----------Question 1.2----------")
    question1_2(top_10_eigenvectors_R, top_10_eigenvectors_G, top_10_eigenvectors_B)

    print("----------Question 1.3----------")
    plt.figure(figsize=(12, 6))
    plt.subplot(2, 4, 1)
    plt.imshow(img_reconstruct)
    plt.title('Original Image')
    plt.axis('off')

    ks = [1, 50, 250, 500, 1000, 4096]
    for i, k in enumerate(ks):
        plt.subplot(2, 4, i + 2)
        plt.imshow(question1_3(X, k, index_reconstruct))
        plt.title(f'k = {k}')
        plt.axis('off')
    plt.show()


    # QUESTION 2 MAIN

    X_train, y_train, X_test, y_test = read_dataset(sys.argv[2]) 

    X_validation = X_train[:10000]
    y_validation = y_train[:10000]

    X_train = X_train[10000:]
    y_train = y_train[10000:]
    
    print("----------Question 2.1----------")
    weights, metrics = train_and_evaluate(X_train, y_train, X_validation, y_validation, X_test, y_test,
                                          num_classes=10, batch_size=200, learning_rate=5e-4,
                                          reg_coeff=1e-4, init_type="normal", epochs=100)

    print("Final Test Accuracy of the Default Model:", metrics["test_accuracy"])
    print("Confusion Matrix:")
    print(metrics["confusion_matrix"])

    print("----------Question 2.2----------")
    results = run_experiments(X_train, y_train, X_validation, y_validation, X_test, y_test, num_classes=10, epochs=100)

    for key, metrics in results.items():
        print(f"--- Results for {key} ---")
        print(f"Test Accuracy: {metrics['test_accuracy']}")
        print(f"Confusion Matrix:\n{metrics['confusion_matrix']}")
        print(f"Validation Accuracies: {metrics['val_accuracies'][-5:]} (Last 5 epochs)\n")

    plot_validation_accuracy(results, "batch_size", "Validation Accuracy Trends for Batch Sizes")

    plot_validation_accuracy(results, "learning_rate", "Validation Accuracy Trends for Learning Rates")

    plot_validation_accuracy(results, "init_type", "Validation Accuracy Trends for Weight Initialization")

    plot_validation_accuracy(results, "reg_coeff", "Validation Accuracy Trends for Regularization Coefficients")

    print("----------Question 2.3----------")

    weights, metrics = train_and_evaluate(X_train, y_train, X_validation, y_validation, X_test, y_test, num_classes=10, 
                                          reg_coeff=0.0001, init_type="zero", epochs=100)

    print("Final Test Accuracy of Best Model:", metrics["test_accuracy"])
    print("Confusion Matrix:")
    print(metrics["confusion_matrix"])

    print("----------Question 2.4----------")

    visualize_weights(weights,
                      class_names=["T-shirt", "Trouser", "Pullover", "Dress", "Coat", "Sandal", "Shirt", "Sneaker",
                                   "Bag", "Boot"])

    print("----------Question 2.5----------")

    conf_matrix = metrics["confusion_matrix"]
    metrics_results = compute_metrics(conf_matrix)

    print_metrics(metrics_results,
                  class_names=["T-shirt", "Trouser", "Pullover", "Dress", "Coat", "Sandal", "Shirt", "Sneaker", "Bag",
                               "Boot"])


if __name__ == "__main__":
    main()
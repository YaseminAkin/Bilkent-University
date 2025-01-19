import os
import sys
import numpy as np
import pandas as pd


# helper functions


def load_dataset(dataset_dir=sys.argv[1]):
    x_train_csv_path = os.path.join(dataset_dir, 'x_train.csv')
    y_train_csv_path = os.path.join(dataset_dir, 'y_train.csv')
    x_test_csv_path = os.path.join(dataset_dir, 'x_test.csv')
    y_test_csv_path = os.path.join(dataset_dir, 'y_test.csv')

    x_train = pd.read_csv(x_train_csv_path, header=0)
    y_train = pd.read_csv(y_train_csv_path, header=None)
    x_test = pd.read_csv(x_test_csv_path, header=0)
    y_test = pd.read_csv(y_test_csv_path, header=None)

    # convert to numpy arrays
    x_train = x_train.to_numpy()
    y_train = y_train.to_numpy().flatten()
    x_test = x_test.to_numpy()
    y_test = y_test.to_numpy().flatten()

    return x_train, y_train, x_test, y_test


def calc_accuracy(y_test, y_pred):
    correct = 0
    for pred, test in zip(y_pred, y_test):
        if test == pred:
            correct += 1
    return correct / len(y_test)


def calculate_confusion_matrix(y_test, y_pred):
    labels = sorted(set(y_test))
    confusionMatrix = [[0 for label in labels] for label in labels]

    for true, pred in zip(y_test, y_pred):
        confusionMatrix[true][pred] += 1

    return confusionMatrix


# classes of models


class MultinomialNaiveBayes:
    def __init__(self):
        self.y_train = None
        self.x_train = None
        self.class_priors = {}
        self.class_likelihoods = {}
        self.class_word_counts = {}
        self.vocab = {}

    def fit(self, x_train, y_train):
        self.x_train = x_train
        self.y_train = y_train
        self.class_priors = self.calc_class_prior(self.y_train)
        self.class_likelihoods = self.calc_class_likelihood(self.x_train, self.y_train)

    def fit_with_smoothing(self, x_train, y_train):
        self.x_train = x_train
        self.y_train = y_train
        self.class_priors = self.calc_class_prior(self.y_train)
        self.class_likelihoods = self.calc_class_likelihood_dirichlet(self.x_train, self.y_train)

    def calc_class_prior(self, y_train):
        total_count = len(y_train)
        for label in y_train:
            if label not in self.class_priors:
                self.class_priors[label] = 1
            else:
                self.class_priors[label] += 1

        for label in self.class_priors:
            self.class_priors[label] /= total_count

        return self.class_priors

    def calc_class_likelihood(self, x_train, y_train):
        self.vocab = list(range(x_train.shape[1]))

        self.class_word_counts = {label: 0 for label in self.class_priors}
        self.class_likelihoods = {label: {word: 0 for word in self.vocab} for label in self.class_priors}

        for review, label in zip(x_train, y_train):
            for word, count in enumerate(review):
                self.class_likelihoods[label][word] += count
                self.class_word_counts[label] += count

        for label in self.class_likelihoods:
            for word in self.class_likelihoods[label]:
                if self.class_word_counts[label] > 0:
                    self.class_likelihoods[label][word] /= self.class_word_counts[label]

        return self.class_likelihoods

    def calc_class_likelihood_dirichlet(self, x_train, y_train):
        self.vocab = list(range(x_train.shape[1]))

        self.class_likelihoods = {label: {word: 1 for word in self.vocab} for label in self.class_priors}
        self.class_word_counts = {label: 1 * len(self.vocab) for label in self.class_priors}

        for review, label in zip(x_train, y_train):
            for word, count in enumerate(review):
                self.class_likelihoods[label][word] += count
                self.class_word_counts[label] += count

        for label in self.class_likelihoods:
            for word in self.class_likelihoods[label]:
                if self.class_word_counts[label] > 0:
                    self.class_likelihoods[label][word] /= self.class_word_counts[label]

        return self.class_likelihoods

    def classify(self, x):
        class_scores = {}
        for label in self.class_priors:
            # taken log0 as -1e12
            class_scores[label] = np.log(self.class_priors[label]) if self.class_priors[label] > 0 else -1e12
            for word, count in enumerate(x):
                if self.class_likelihoods[label][word] > 0:
                    class_scores[label] += count * np.log(self.class_likelihoods[label][word])
                else:
                    class_scores[label] += count * -1e12

        return min([label for label in class_scores if class_scores[label] == max(class_scores.values())])

    def predict(self, x_test):
        y_pred = []
        for x in x_test:
            y_pred.append(self.classify(x))
        return y_pred


class BernoulliNaiveBayes:
    def __init__(self):
        self.y_train = None
        self.x_train = None
        self.class_priors = {}
        self.class_likelihoods = {}
        self.class_counts = {}

    def fit(self, x_train, y_train):
        self.x_train = x_train
        self.y_train = y_train
        self.class_priors = self.calc_class_prior(self.y_train)
        self.class_likelihoods = self.calc_class_likelihood(self.x_train, self.y_train)

    def calc_class_prior(self, y_train):
        total_count = len(y_train)
        for label in y_train:
            if label not in self.class_priors:
                self.class_priors[label] = 1
            else:
                self.class_priors[label] += 1

        for label in self.class_priors:
            self.class_priors[label] /= total_count

        return self.class_priors

    def calc_class_likelihood(self, x_train, y_train):
        vocab = range(x_train.shape[1])

        self.class_counts = {label: 2 for label in self.class_priors}
        self.class_likelihoods = {label: {word: 1 for word in vocab} for label in self.class_priors}

        for review, label in zip(x_train, y_train):
            self.class_counts[label] += 1
            for word in range(len(review)):
                if review[word] > 0:
                    self.class_likelihoods[label][word] += 1

        for label in self.class_likelihoods:
            for word in self.class_likelihoods[label]:
                if self.class_counts[label] > 0:
                    self.class_likelihoods[label][word] /= self.class_counts[label]

        return self.class_likelihoods

    def classify(self, x):
        class_scores = {}
        for label in self.class_priors:
            # taken log0 as -1e12
            class_scores[label] = np.log(self.class_priors[label]) if self.class_priors[label] > 0 else -1e12
            for word in range(len(x)):
                if x[word] > 0:
                    class_scores[label] += np.log(self.class_likelihoods[label][word]) if self.class_likelihoods[label][
                                                                                              word] > 0 else -1e12
                else:
                    if self.class_likelihoods[label][word] == 1:
                        class_scores[label] += 0  # 0 * log(0) = 0
                    else:
                        class_scores[label] += np.log(1 - self.class_likelihoods[label][word]) if (1 -
                                                                                                   self.class_likelihoods[
                                                                                                       label][
                                                                                                       word]) > 0 else -1e12

        return min([label for label in class_scores if class_scores[label] == max(class_scores.values())])

    def predict(self, x_test):
        y_pred = []
        for x in x_test:
            y_pred.append(self.classify(x))
        return y_pred


# main()
def main():
    x_train, y_train, x_test, y_test = load_dataset()
    multinomialNaiveBayes = MultinomialNaiveBayes()
    print("Results without Smoothing:")
    multinomialNaiveBayes.fit(x_train, y_train)
    y_pred = multinomialNaiveBayes.predict(x_test)
    accuracy = calc_accuracy(y_test, y_pred)
    print("Accuracy: {:.3f}".format(accuracy))
    confusionMatrix = calculate_confusion_matrix(y_test, y_pred)
    print("Confusion Matrix:")
    for row in confusionMatrix:
        print(row)
    print()
    x_train, y_train, x_test, y_test = load_dataset()
    multinomialNaiveBayesSmoothed = MultinomialNaiveBayes()
    print("Results with Smoothing:")
    multinomialNaiveBayesSmoothed.fit_with_smoothing(x_train, y_train)
    y_pred = multinomialNaiveBayesSmoothed.predict(x_test)
    accuracy = calc_accuracy(y_test, y_pred)
    print("Accuracy: {:.3f}".format(accuracy))
    confusionMatrix = calculate_confusion_matrix(y_test, y_pred)
    print("Confusion Matrix:")
    for row in confusionMatrix:
        print(row)
    print()
    x_train, y_train, x_test, y_test = load_dataset()
    bernoulliNaiveBayes = BernoulliNaiveBayes()
    print("Results with Bernoulli:")
    bernoulliNaiveBayes.fit(x_train, y_train)
    y_pred = bernoulliNaiveBayes.predict(x_test)
    accuracy = calc_accuracy(y_test, y_pred)
    print("Accuracy: {:.3f}".format(accuracy))
    confusionMatrix = calculate_confusion_matrix(y_test, y_pred)
    print("Confusion Matrix:")
    for row in confusionMatrix:
        print(row)


if __name__ == "__main__":
    main()

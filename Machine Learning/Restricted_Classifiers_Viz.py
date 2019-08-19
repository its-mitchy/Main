import pandas as pd
import numpy as np
import datetime
import matplotlib.pyplot as plt
import matplotlib

from sklearn import preprocessing, model_selection, svm, naive_bayes, ensemble, tree, neighbors, metrics
from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer
from sklearn.model_selection import GridSearchCV

def start_timer():
    start_time = datetime.datetime.now()
    print("Start time: " + str(start_time))
    return start_time

def end_timer():
    end_time = datetime.datetime.now()
    print("End time: " + str(end_time))
    return end_time

def calculate_time(start_time, end_time):
    elapsed_time = end_time - start_time
    print("Elapsed time: " + str(elapsed_time))

def prepare_dataset():
    df_raw = pd.read_excel('Data-Descriptive-Stats.xlsx', sheet_name = 'data_set')
    df_raw.drop(columns = ['APP_ID', 'APP_NM', 'TABLE_NM'], inplace = True)
    return df_raw.fillna(' ')

def set_model(classifier):
    param_grid = {'alpha': [1e-10, 1e-1, 1, 10]}

    if classifier == 'MNB':
        clf = naive_bayes.MultinomialNB(alpha=1e-10,class_prior=[.1,.9]) 
        param_grid = {'alpha': [1e-10, 1e-1, 1, 10], 'class_prior': [[.1,.9],[.25,.5],[.75,.25]]}
    elif classifier == 'BNB':
        clf = naive_bayes.BernoulliNB(alpha=1e-10,class_prior=[.1,.9])
    elif classifier == 'CNB':
        clf = naive_bayes.ComplementNB(alpha=1e-10,norm=True)
    elif classifier == 'KNN':
        clf = neighbors.KNeighborsClassifier(n_neighbors=1)
    elif classifier == 'SVM':
        clf = svm.SVC(kernel='linear') 
        param_grid = {'C': [1e-3, 1]} 
    elif classifier == 'DT':
        clf = tree.DecisionTreeClassifier()
    elif classifier == 'RF':
        clf = ensemble.RandomForestClassifier()
    else:
        print("Please enter a valid model.")
        raise SystemExit

    return clf, param_grid

def run_model():
    df = prepare_dataset()
    features = np.array(df.drop(['RESTRICTED'], 1)).flatten()

    # This implements scikit learn's more optimized version of bag of words model
    count_vect = CountVectorizer()
    X = count_vect.fit_transform(features)

    tfidf_transformer = TfidfTransformer() # term Frequency * inverse of document frequency. This removes weight of doc length and removes weight of common words. 
    X = tfidf_transformer.fit_transform(X)  # X.shape?

    y = np.array(df['RESTRICTED'])

    X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=.2)

    clf, param_grid = set_model(classifier)
    #clf = GridSearchCV(clf, param_grid, scoring='recall', cv=5)

    clf = clf.fit(X_train, y_train)
    #print(clf.best_score_)
    #print(clf.best_params_)
    #print(clf.cv_results_)
    y_pred = clf.predict(X_test)

    accuracy = clf.score(X_test, y_test)


    return accuracy, X_test, y_test, y_pred
    

def print_metrics(accuracy, X_test, y_test, y_pred):
    print("\n\n")

    # Our biggest concern is false negatives. If we classify a Y as a N then that is bad. 
    print("Confusion Matrix:")
    print(str(metrics.confusion_matrix(y_test, y_pred)))
    print("\n\n")
    size = [metrics.confusion_matrix(y_test,y_pred)[0][0],metrics.confusion_matrix(y_test,y_pred)[0][1],metrics.confusion_matrix(y_test,y_pred)[1][0],metrics.confusion_matrix(y_test,y_pred)[1][1]]
    labels = 'Positives', 'False Positives', 'Negatives', 'False Negatives'
    explode = (0,.1,0,.1)
    fig1, ax1 = plt.subplots()
    ax1.pie(size, explode=explode, labels = labels)
    ax1.axis('equal')
    plt.show()
    
    #Recall is the ability of a model to find all the relevant cases within a dataset. We want to maximize this.
    #Recall = TP/(TP+FN)
    #Precision = TP/(TP+FP). Precision is not super important since we don't care too much if we classify non restricted data as restricted.
    print("Metrics:")
    print(metrics.classification_report(y_test, y_pred))
    print("\n\n")

    print("Overall Accuracy: " + str(accuracy * 100) + "%")

try:
    classifier = input("Please enter the classifier you want to use: MNB, BNB, CNB, DT, RF, KNN, or SVM.\n")
except:
    print("Please enter a valid input.")
    raise SystemExit

start_time = start_timer()

accuracy, X_test, y_test, y_pred = run_model()
print_metrics(accuracy, X_test, y_test, y_pred)

end_time = end_timer()
calculate_time(start_time, end_time)



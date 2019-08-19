import pandas as pd
import numpy as np
import datetime
import matplotlib.pyplot as plt
import matplotlib
import pyodbc

from sklearn import preprocessing, model_selection, svm, naive_bayes, ensemble, tree, neighbors, metrics, neural_network
from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer
from sklearn.model_selection import GridSearchCV

sql_conn = pyodbc.connect("Driver={SQL Server Native Client 11.0};"
                      "Server=SQLSERVER2017;"
                      "Database=CGI_DATA;"
                      "Trusted_Connection=yes;")

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
    # Define a parameter to access the cursor method:
    cursor = sql_conn.cursor()

    # Pass the query string into the cursor method:
    cursor.execute(query_str)
    sql_conn.commit()

    query = "SELECT [COLUMN_NM],[RESTRICTED] FROM [CGIDATA]"
    df = pd.read_sql(query, sql_conn)
    return df.fillna(' ')

def set_model(classifier):
    param_grid = {}

    if classifier == 'MNB':
        clf = naive_bayes.MultinomialNB(alpha=1e-10) 
        param_grid={'class_prior':[[.5,.5],[.48,.52],[.45,.55],[.4,.6],[.6,.4],[.75,.25],[.25,.75],[.9,.1],[.1,.9]], 'alpha':[1e-10,1e-1,1,10,100]}
    elif classifier == 'BNB':
        clf = naive_bayes.BernoulliNB(alpha=1e-1)
    elif classifier == 'CNB':
        clf = naive_bayes.ComplementNB(norm=True)
    elif classifier == 'KNN':
        clf = neighbors.KNeighborsClassifier(n_neighbors=1)
        param_grid={'n_neighbors':[1,5,10], 'leaf_size':[10,30,50]}
        #param_grid = {'p': [1,2], 'n_neighbors':[1,2,3,4,5,6,7,8,9,10], 'leaf_size':[10,20,30,40,50], 'weights':['uniform','distance'], 'algorithm':['auto','ball_tree','kd_tree','brute']}
    elif classifier == 'SVM':
        clf = svm.LinearSVC(C=10) 
        param_grid = {'C':[.001,.01,.1,1,10,100]}
        #param_grid = {'tol': [1e-3, 1e-4, 1e-5, 1e-6], 'dual':[True, False], 'max_iter':[1000,10000], 'C': [.001, .01, .1, 10, 100, 1000], 'class_weight': [{'Y':1.5, 'N':1}, {'Y':3, 'N':1.5}, {'Y':1, 'N':.75}, {'Y':1, 'N':.4}, {'Y':.75, 'N':.25}, {'Y':1, 'N':3}]}
    elif classifier == 'DT':
        clf = tree.DecisionTreeClassifier()
        param_grid={'max_depth':[None,10,100,1000,10000],'min_weight_fraction_leaf':[0,.01,.1,.2,.3,.4,.5]}
    elif classifier == 'RF':
        clf = ensemble.RandomForestClassifier()
    elif classifier == 'NN':
        clf = neural_network.MLPClassifier()
    elif classifier == 'do_all':
        clf = 'all'
    else:
        print("Please enter a valid model.")
        raise SystemExit

    return clf, param_grid

def document_everything(X_train, X_test, y_train, y_test):
    Reports = {}
    Accuracies = {}
    conf_matrices = {}
    
    clf = svm.LinearSVC(C=10)
    clf = clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    Accuracies['SVM'] = clf.score(X_test, y_test)
    Reports['SVM'] = metrics.classification_report(y_test, y_pred)
    conf_matrices['SVM'] = metrics.confusion_matrix(y_test, y_pred)

    print('SVM Done')

    clf = ensemble.RandomForestClassifier()
    clf = clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    Accuracies['RF'] = clf.score(X_test, y_test)
    Reports['RF'] = metrics.classification_report(y_test, y_pred)
    conf_matrices['RF'] = metrics.confusion_matrix(y_test, y_pred)

    print('RF Done')

    clf = tree.DecisionTreeClassifier()
    clf = clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    Accuracies['DT'] = clf.score(X_test, y_test)
    Reports['DT'] = metrics.classification_report(y_test, y_pred)
    conf_matrices['DT'] = metrics.confusion_matrix(y_test, y_pred)

    print('DT Done')
    
    clf = neighbors.KNeighborsClassifier(n_neighbors=1,leaf_size=10)
    clf = clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    Accuracies['KNN'] = clf.score(X_test, y_test)
    Reports['KNN'] = metrics.classification_report(y_test, y_pred)
    conf_matrices['KNN'] = metrics.confusion_matrix(y_test, y_pred)

    print('KNN Done')

    clf = naive_bayes.MultinomialNB()
    clf = clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    Accuracies['MNB'] = clf.score(X_test, y_test)
    Reports['MNB'] = metrics.classification_report(y_test, y_pred)
    conf_matrices['MNB'] = metrics.confusion_matrix(y_test, y_pred)
    
    print('MNB Done')
    
    clf = naive_bayes.BernoulliNB(alpha=1e-10)
    clf = clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    Accuracies['BNB'] = clf.score(X_test, y_test)
    Reports['BNB'] = metrics.classification_report(y_test, y_pred)
    conf_matrices['BNB'] = metrics.confusion_matrix(y_test, y_pred)

    print('BNB Done')

    clf = naive_bayes.ComplementNB()
    clf = clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    Accuracies['CNB'] = clf.score(X_test, y_test)
    Reports['CNB'] = metrics.classification_report(y_test, y_pred)
    conf_matrices['CNB'] = metrics.confusion_matrix(y_test, y_pred)

    print('CNB Done')
    
    clf = neural_network.MLPClassifier()
    clf = clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    Accuracies['MLP'] = clf.score(X_test, y_test)
    Reports['MLP'] = metrics.classification_report(y_test, y_pred)
    conf_matrices['MLP'] = metrics.confusion_matrix(y_test, y_pred)

    print('CNB Done')

    for clf in Reports:
        print(str(clf))
        print(str(Accuracies[clf]))
        print(str(Reports[clf]))
        print(str(conf_matrices[clf]))
        size = [conf_matrices[clf][0][0],conf_matrices[clf][0][1],conf_matrices[clf][1][0],conf_matrices[clf][1][1]]
        labels = 'True Negatives', 'False Positive', 'False Negative', 'True Positives'
        explode = (0,.1,0,.1)
        fig1, ax1 = plt.subplots()
        ax1.pie(size, explode=explode, labels = labels)
        ax1.axis('equal')
        plt.show()

        
def run_model():
    df = prepare_dataset()
    train_data = df.drop(['RESTRICTED'],1)
    features = np.array([train_data.iloc[:,0]+train_data.iloc[:,2]]).flatten()
    
    # This implements scikit learn's more optimized version of bag of words model
    count_vect = CountVectorizer()
    X = count_vect.fit_transform(features)
    X.shape
    
    tfidf_transformer = TfidfTransformer() # term Frequency * inverse of document frequency. This removes weight of doc length and removes weight of common words. 
    X = tfidf_transformer.fit_transform(X)  # X.shape?
    X.shape
    
    y = np.array(df['RESTRICTED'])

    X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=.1)

    clf, param_grid = set_model(classifier)
    if clf == 'all':
        document_everything(X_train, X_test, y_train, y_test)
    else:
        clf = GridSearchCV(clf, param_grid, cv=5)
    
        clf = clf.fit(X_train, y_train)
        print(str(clf.best_score_))
            print(str(clf.best_params_))
        print(str(clf.cv_results_))
        y_pred = clf.predict(X_test)
    
        accuracy = clf.score(X_test, y_test)
    
        print_metrics(accuracy, X_test, y_test, y_pred)
    
    

def print_metrics(accuracy, X_test, y_test, y_pred):
    print("\n\n")

    # Our biggest concern is false negatives. If we classify a Y as a N then that is bad. 
    print("Confusion Matrix:")
    print(str(metrics.confusion_matrix(y_test, y_pred)))
    print("\n\n")
    size = [metrics.confusion_matrix(y_test,y_pred)[0][0],metrics.confusion_matrix(y_test,y_pred)[0][1],metrics.confusion_matrix(y_test,y_pred)[1][0],metrics.confusion_matrix(y_test,y_pred)[1][1]]
    labels = 'True Negatives', 'False Positive', 'False Negative', 'True Positives'
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
    classifier = input("Please enter the classifier you want to use: MNB, BNB, CNB, DT, RF, KNN, SVM, NN, or do_all.\n")
except:
    print("Please enter a valid input.")
    raise SystemExit

start_time = start_timer()

run_model()

end_time = end_timer()
calculate_time(start_time, end_time)



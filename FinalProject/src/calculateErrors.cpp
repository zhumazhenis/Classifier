/*
 * calculateErrors.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: General
 */

#include "calculateErrors.h"

void calculateErrors(
		double** X,
		int* y,
		int N_trn,
		int N_tst,
		int D,
		int d,
		long* seed,
		AllErrors* all_errors)
{
	double dinit = 0.00;

	/*22-25lines int N_bolster = 25; // number of bolster sample point
	int K = 5; // k-fold CV
	int R = 10; // number of iterations in CV
	int B = 100; // number of bootstrap replicates*/

	SimulationData data_trn;
	SimulationData data_tst;

	int* best_features;

	LDA model_LDA;
	DLDA model_DLDA;
	G13 model_G13;
	QDA model_QDA;
	SEDC model_SEDC;

	svm_model *model_LSVM;	//svm training model
	svm_node *subdata_LSVM;	//svm training data
	svm_problem subcl_LSVM;	//svm training data structure

	svm_model *model_KSVM;	//svm training model
	svm_node *subdata_KSVM;	//svm training data
	svm_problem subcl_KSVM;	//svm training data structure

	(*all_errors).lda_true_error = 0.00;
	(*all_errors).lsvm_true_error = 0.00;
	(*all_errors).ksvm_true_error = 0.00;
	(*all_errors).dlda_true_error = 0.00;
    (*all_errors).g13_true_error = 0.00;
    (*all_errors).qda_true_error = 0.00;
    (*all_errors).sedc_true_error = 0.00;

	/*46-60 lines (*all_errors).lda_resub_error = 0.00;
	(*all_errors).lsvm_resub_error = 0.00;
	(*all_errors).ksvm_resub_error = 0.00;

	(*all_errors).lda_bolster_error = 0.00;
	(*all_errors).lsvm_bolster_error = 0.00;
	(*all_errors).ksvm_bolster_error = 0.00;

	(*all_errors).lda_loo_error = 0.00;
	(*all_errors).lsvm_loo_error = 0.00;
	(*all_errors).ksvm_loo_error = 0.00;

	(*all_errors).lda_cvkfold_error = 0.00;
	(*all_errors).lsvm_cvkfold_error = 0.00;
	(*all_errors).ksvm_cvkfold_error = 0.00;*/

	data_trn.data = make_2D_matrix(N_trn, D, dinit);
	data_trn.labels = new int [N_trn];
	data_tst.data = make_2D_matrix(N_tst, D, dinit);
	data_tst.labels = new int [N_tst];

	dataGeneration(X, y, N_trn, N_tst, D, seed, &data_trn, &data_tst);

	best_features = new int [d];
	featureSelection(data_trn.data, data_trn.labels, data_trn.N, data_trn.D, d, best_features);

	model_LDA.a = new double [d];
	ldaTrn(data_trn.data, data_trn.labels, data_trn.N, d, best_features, &model_LDA);

	model_LSVM = svmTrn(data_trn.data, data_trn.labels, data_trn.N, d, best_features, 0, &subdata_LSVM, &subcl_LSVM);
	model_KSVM = svmTrn(data_trn.data, data_trn.labels, data_trn.N, d, best_features, 2, &subdata_KSVM, &subcl_KSVM);

	model_DLDA.a = new double [d];
	dldaTrn(data_trn.data, data_trn.labels, data_trn.N, d, best_features, &model_DLDA);

	model_G13.a = new double [d];
	g13Trn(data_trn.data, data_trn.labels, data_trn.N, d, best_features, &model_G13);

	model_QDA.a = make_2D_matrix(d, d, dinit);
	model_QDA.b = new double [d];
	qdaTrn(data_trn.data, data_trn.labels, data_trn.N, d, best_features, &model_QDA);

	sedcTrn(data_trn.data, data_trn.labels, data_trn.N, d, best_features, &model_SEDC);

	(*all_errors).lda_true_error = ldaTst(data_tst.data, data_tst.labels, data_tst.N, d, best_features, model_LDA);
	(*all_errors).lsvm_true_error = svmTst(data_tst.data, data_tst.labels, data_tst.N, d, best_features, model_LSVM);
	(*all_errors).ksvm_true_error = svmTst(data_tst.data, data_tst.labels, data_tst.N, d, best_features, model_KSVM);

	(*all_errors).dlda_true_error = dldaTst(data_tst.data, data_tst.labels, data_tst.N, d, best_features, model_DLDA);
	(*all_errors).g13_true_error = g13Tst(data_tst.data, data_tst.labels, data_tst.N, d, best_features, model_G13);
	(*all_errors).qda_true_error = qdaTst(data_tst.data, data_tst.labels, data_tst.N, d, best_features, model_QDA);
    (*all_errors).sedc_true_error = sedcTst(data_tst.data, data_tst.labels, data_tst.N, d, best_features, model_SEDC);

    /*LEVEL4: RLDA_RLDA_RLDA_RLDA_RLDA*/
    RLDA model_RLDA;

    (*all_errors).rlda_true_error = 0.00;

    SimulationData S_1; //S_1 is training data, which is indicated with [2N/3]
	SimulationData S_2; //S_2 is training data, which is indicated with N-[2N/3]

	int* best_features_opt; //best_features_opt will be found using the data_trn.data

    S_1.data = make_2D_matrix((2*N_trn/3), D, dinit);
	S_1.labels = new int [2*N_trn/3];
	S_2.data = make_2D_matrix((N_trn-2*N_trn/3), D, dinit);
	S_2.labels = new int [N_trn-2*N_trn/3];

	dataGeneration(data_trn.data, data_trn.labels, (2*N_trn/3), (N_trn-2*N_trn/3), D, seed, &S_1, &S_2);

	best_features_opt = new int [d];
	featureSelection(S_1.data, S_1.labels, S_1.N, S_1.D, d, best_features_opt);

    int i;
    int y_opt_index;
	double e;
	double minimum_error;

	for(i = 0; i<21; i++) {
        model_RLDA.a = new double [d];

        rldaTrn(S_1.data, S_1.labels, S_1.N, d, best_features_opt, &model_RLDA, i);
        e = rldaTst(S_2.data, S_2.labels, S_2.N, d, best_features_opt, model_RLDA);

        if(i==0){
            minimum_error = e;
            y_opt_index = i;
        }
        if(e<minimum_error) {
            minimum_error = e;
            y_opt_index = i; //y_opt_index is the index of y_opt inside the rldaTrn
        }

        delete model_RLDA.a;
	}

	model_RLDA.a = new double [d];
	rldaTrn(data_trn.data, data_trn.labels, data_trn.N, d, best_features, &model_RLDA, y_opt_index);

	(*all_errors).rlda_true_error = rldaTst(data_tst.data, data_tst.labels, data_tst.N, d, best_features, model_RLDA);

	/*82-100lines(*all_errors).lda_resub_error = ldaTst(data_trn.data, data_trn.labels, data_trn.N, d, best_features, model_LDA);
	(*all_errors).lsvm_resub_error = svmTst(data_trn.data, data_trn.labels, data_trn.N, d, best_features, model_LSVM);
	(*all_errors).ksvm_resub_error = svmTst(data_trn.data, data_trn.labels, data_trn.N, d, best_features, model_KSVM);

	(*all_errors).lda_bolster_error = ldaBolster(data_trn.data, data_trn.labels, data_trn.N, d, best_features, model_LDA);
	(*all_errors).lsvm_bolster_error = lsvmBolster(data_trn.data, data_trn.labels, data_trn.N, d, best_features, N_bolster, seed);
	(*all_errors).ksvm_bolster_error = ksvmBolster(data_trn.data, data_trn.labels, data_trn.N, d, best_features, N_bolster, seed);

	(*all_errors).lda_loo_error = ldaLOO(data_trn.data, data_trn.labels, data_trn.N, data_trn.D, d);
	(*all_errors).lsvm_loo_error = lsvmLOO(data_trn.data, data_trn.labels, data_trn.N, data_trn.D, d);
	(*all_errors).ksvm_loo_error = ksvmLOO(data_trn.data, data_trn.labels, data_trn.N, data_trn.D, d);

	(*all_errors).lda_cvkfold_error = ldaCVkFold(data_trn.data, data_trn.labels, data_trn.N, data_trn.D, d, K, R, seed);
	(*all_errors).lsvm_cvkfold_error = lsvmCVkFold(data_trn.data, data_trn.labels, data_trn.N, data_trn.D, d, K, R, seed);
	(*all_errors).ksvm_cvkfold_error = ksvmCVkFold(data_trn.data, data_trn.labels, data_trn.N, data_trn.D, d, K, R, seed);

	(*all_errors).lda_boot632_error = ldaBoot632(data_trn.data, data_trn.labels, data_trn.N, data_trn.D, d, B, (*all_errors).lda_resub_error, seed);
	(*all_errors).lsvm_boot632_error = lsvmBoot632(data_trn.data, data_trn.labels, data_trn.N, data_trn.D, d, B, (*all_errors).lsvm_resub_error, seed);
	(*all_errors).ksvm_boot632_error = ksvmBoot632(data_trn.data, data_trn.labels, data_trn.N, data_trn.D, d, B, (*all_errors).ksvm_resub_error, seed);*/

	delete model_LDA.a;
    delete model_DLDA.a;
	delete model_G13.a;
	delete_2D_matrix(d, d, model_QDA.a);
	delete model_QDA.b;
	delete model_RLDA.a;

	delete best_features;
	delete best_features_opt;


	svmDestroy(model_LSVM, subdata_LSVM, &subcl_LSVM);
	svmDestroy(model_KSVM, subdata_KSVM, &subcl_KSVM);

	delete_2D_matrix(N_trn, D, data_trn.data);
	delete data_trn.labels;
	delete_2D_matrix(N_tst, D, data_tst.data);
	delete data_tst.labels;

	delete_2D_matrix((2*N_trn/3), S_1.D, S_1.data);
	delete S_1.labels;
	delete_2D_matrix((N_trn-2*N_trn/3), S_2.D, S_2.data);
	delete S_2.labels;

	return;
}

#include "NeuralNetwork.h"
#include "ActivationFunctions.h"
#include "CostFunctions.h"
#include "GradientCheck.h"

static double sweights[] = { 0.35778736,  0.56078453,  1.08305124,  1.05380205, -1.37766937, -0.93782504,
  0.51503527,  0.51378595,  0.51504769 , 3.85273149 , 0.57089051,  1.13556564,
  0.95400176,  0.65139125, -0.31526924 , 0.75896922, -0.77282521, -0.23681861,
 -0.48536355,  0.08187414,  2.31465857, -1.86726519,  0.68626019 ,-1.61271587,
 -0.47193187,  1.0889506 ,  0.06428002, -1.07774478, -0.71530371 , 0.67959775,
 -0.73036663,  0.21645859,  0.04557184, -0.65160035,  2.14394409 , 0.63391902,
 -2.02514259,  0.18645431, -0.66178646,  0.85243333, -0.79252074 ,-0.11473644,
  0.50498728,  0.86575519, -1.20029641, -0.33450124, -0.47494531 ,-0.65332923,
  1.76545424,  0.40498171, -1.26088395,  0.91786195,  2.1221562  , 1.03246526,
 -1.51936997, -0.48423407,  1.26691115, -0.70766947,  0.44381943 , 0.77463405,
 -0.92693047, -0.05952536, -3.24126734, -1.02438764, -0.25256815 ,-1.24778318,
  1.6324113 , -1.43014138, -0.44004449,  0.13074058,  1.44127329 ,-1.43586215,
  1.16316375,  0.01023306, -0.98150865,  0.46210347,  0.1990597  ,-0.60021688,
  0.06980208, -0.3853136 ,  0.11351735,  0.66213067,  1.58601682 ,-1.2378155,
  2.13303337, -1.9520878 , -0.1517851 ,  0.58831721,  0.28099187 ,-0.62269952,
 -0.20812225, -0.49300093, -0.58936476,  0.8496021 ,  0.35701549 ,-0.6929096,
  0.89959988,  0.30729952,  0.81286212,  0.62962884, -0.82899501 ,-0.56018104,
  0.74729361,  0.61037027, -0.02090159,  0.11732738,  1.2776649  ,-0.59157139,
  0.54709738, -0.20219265, -0.2176812 ,  1.09877685,  0.82541635 , 0.81350964,
  1.30547881};

double neuralNetworkFunction(const std::vector<double> &weights, std::vector<double> &grad)
{
    NeuralNetwork<double> network;
    std::vector<unsigned int> layerCounts;
    layerCounts.push_back(5);
    network.init(10,10,layerCounts, sigmoid<double>, sigmoid<double>, crossEntropy<double>, derivativeCrossEntropySigmoid<double>);

    network.assignWeights(weights);

    double inputs[20][10] = {{ 0.49671415, -0.1382643,   0.64768854,  1.52302986, -0.23415337, -0.23413696,
       1.57921282,  0.76743473, -0.46947439,  0.54256004},
     {-0.46341769, -0.46572975,  0.24196227, -1.91328024, -1.72491783, -0.56228753,
      -1.01283112,  0.31424733, -0.90802408, -1.4123037 },
     { 1.46564877, -0.2257763,  0.0675282,  -1.42474819, -0.54438272,  0.11092259,
      -1.15099358,  0.37569802, -0.60063869, -0.29169375},
     {-0.60170661,  1.85227818, -0.01349722, -1.05771093,  0.82254491, -1.22084365,
       0.2088636, -1.95967012, -1.32818605,  0.19686124},
     { 0.73846658,  0.17136828, -0.11564828, -0.3011037,  -1.47852199, -0.71984421,
      -0.46063877,  1.05712223,  0.34361829, -1.76304016},
     { 0.32408397, -0.38508228, -0.676922,    0.61167629,  1.03099952,  0.93128012,
      -0.83921752, -0.30921238,  0.33126343,  0.97554513},
     {-0.47917424, -0.18565898, -1.10633497, -1.19620662,  0.81252582,  1.35624003,
      -0.07201012,  1.0035329,   0.36163603, -0.64511975},
     { 0.36139561,  1.53803657, -0.03582604,  1.56464366, -2.6197451,   0.8219025,
       0.08704707, -0.29900735,  0.09176078, -1.98756891},
     {-0.21967189,  0.35711257,  1.47789404, -0.51827022, -0.8084936,  -0.50175704,
       0.91540212,  0.32875111, -0.5297602,   0.51326743},
     { 0.09707755,  0.96864499, -0.70205309, -0.32766215, -0.39210815, -1.46351495,
       0.29612028,  0.26105527,  0.00511346, -0.23458713},
     {-1.41537074, -0.42064532, -0.34271452, -0.80227727, -0.16128571,  0.40405086,
       1.8861859,   0.17457781,  0.25755039, -0.07444592},
     {-1.91877122, -0.02651388,  0.06023021,  2.46324211, -0.19236096,  0.30154734,
      -0.03471177, -1.16867804,  1.14282281,  0.75193303},
     { 0.79103195, -0.90938745,  1.40279431, -1.40185106,  0.58685709,  2.19045563,
      -0.99053633, -0.56629773,  0.09965137, -0.50347565},
     {-1.55066343,  0.06856297, -1.06230371,  0.47359243, -0.91942423,  1.54993441,
      -0.78325329, -0.32206152,  0.81351722, -1.23086432},
     { 0.22745993,  1.30714275, -1.60748323,  0.18463386,  0.25988279,  0.78182287,
      -1.23695071, -1.32045661,  0.52194157,  0.29698467},
     { 0.25049285,  0.34644821, -0.68002472,  0.2322537,   0.29307247, -0.71435142,
       1.86577451,  0.47383292, -1.1913035,   0.65655361},
     {-0.97468167,  0.7870846,   1.15859558, -0.82068232,  0.96337613,  0.41278093,
       0.82206016,  1.89679298, -0.24538812, -0.75373616},
     {-0.88951443, -0.81581028, -0.07710171,  0.34115197,  0.2766908,   0.82718325,
       0.01300189,  1.45353408, -0.26465683,  2.72016917},
     { 0.62566735, -0.85715756, -1.0708925,   0.48247242, -0.22346279,  0.71400049,
       0.47323762, -0.07282891, -0.84679372, -1.51484722},
     {-0.44651495,  0.85639879,  0.21409374, -1.24573878,  0.17318093,  0.38531738,
      -0.88385744,  0.15372511,  0.05820872, -1.1429703 }};

    std::vector<double> x;
    for(int i = 0; i< 20; ++i)
    {
        for(int e =0 ; e< 10; ++e)
        {
            x.push_back(inputs[i][e]);
        }
    }

    double labels[20][10] =
    {{ 1.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.},
     { 0.,  1.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.},
     { 0.,  0.,  1.,  0.,  0.,  0.,  0.,  0.,  0.,  0.},
     { 0.,  0.,  0.,  1.,  0.,  0.,  0.,  0.,  0.,  0.},
     { 0.,  0.,  0.,  0.,  1.,  0.,  0.,  0.,  0.,  0.},
     { 0.,  0.,  0.,  0.,  0.,  1.,  0.,  0.,  0.,  0.},
     { 0.,  0.,  0.,  0.,  0.,  0.,  1.,  0.,  0.,  0.},
     { 0.,  0.,  0.,  0.,  0.,  0.,  0.,  1.,  0.,  0.},
     { 0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  1.,  0.},
     { 0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  1.},
     { 1.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.},
     { 0.,  1.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.},
     { 0.,  0.,  1.,  0.,  0.,  0.,  0.,  0.,  0.,  0.},
     { 0.,  0.,  0.,  1.,  0.,  0.,  0.,  0.,  0.,  0.},
     { 0.,  0.,  0.,  0.,  1.,  0.,  0.,  0.,  0.,  0.},
     { 0.,  0.,  0.,  0.,  0.,  1.,  0.,  0.,  0.,  0.},
     { 0.,  0.,  0.,  0.,  0.,  0.,  1.,  0.,  0.,  0.},
     { 0.,  0.,  0.,  0.,  0.,  0.,  0.,  1.,  0.,  0.},
     { 0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  1.,  0.},
     { 0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  1.}};

    NeuralNetwork<double>::MiniBatch miniBatch;

    int offset = 0;
    for (int i = 0; i< 20; ++i)
    {
        std::vector<double> labelVector;
        labelVector.resize(10);
        memcpy(&labelVector[0], labels[i], 10 * sizeof(double));

        std::vector<double> inputVector;
        inputVector.resize(10);
        memcpy(&inputVector[0], &x[offset], 10 * sizeof(double));

        NeuralNetwork<double>::TrainingData d(inputVector, labelVector);

        miniBatch.push_back(d);

        offset += 10;
    }

    double cost = 0.0;
    std::vector<NeuralNetworkLayer<double>> gradient;
    network.forwardPropagate(miniBatch, cost, gradient);

    grad.clear();
    grad.reserve(x.size());

    for(size_t i = 0; i < gradient.size(); ++i)
    {
        gradient[i].flatten(grad);
    }

    return cost;
}

void testNeuralNetworkGradientCheck()
{
    std::vector<double> initialWeights;

    for(int i = 0; i< 115;++i)
    {
        initialWeights.push_back(sweights[i]);
    }

    if (gradientCheck<double>(neuralNetworkFunction, initialWeights, 1e-4))
    {
        qDebug() << "gradient check passed!";
    }
    else
    {
        qDebug() << "gradient check failed!";
    }
}

void testXORNeuralNetwork()
{
    NeuralNetwork<double> network;
    std::vector<unsigned int> layerCounts;
    layerCounts.push_back(2);
    network.init(2,1,layerCounts, sigmoid<double>, sigmoid<double>, crossEntropy<double>, derivativeCrossEntropySigmoid<double>);

    network.randomWeights();

    srand(time(NULL));

    double rate = 0.02;

    for (int i = 0; i< 1000000; ++i)
    {
        int a = rand() % 2;
        int b = rand() % 2;
        int c = a ^ b;

        NeuralNetwork<double>::MiniBatch miniBatch;
        std::vector<double> labelVector;
        labelVector.push_back(c);


        std::vector<double> inputVector;
        inputVector.push_back(a);
        inputVector.push_back(b);

        NeuralNetwork<double>::TrainingData d(inputVector, labelVector);

        miniBatch.push_back(d);

        double cost;
        std::vector<NeuralNetworkLayer<double>> gradient;

        network.forwardPropagate(miniBatch, cost, gradient);
        qDebug() << "cost" << cost;

        if (i%500000 == 0)
        {
            rate*=0.5;
        }

        network.updateWeights(rate, gradient);
    }

    qDebug() << "Neural network for XOR has trained, now test:";

    int a[] = {0,0,1,1};
    int b[] = {0,1,0,1};
    for(int i = 0; i<4; ++i)
    {
        std::vector<double> inputs;
        inputs.push_back(a[i]);
        inputs.push_back(b[i]);
        std::vector<double> outputs;
        network.getResult(inputs, outputs);
        qDebug() << "a:" << a[i] << "b" << b[i] << "a XOR b" << (a[i]^b[i]) << "Neural Network computed:" << outputs[0];
    }

}

void testXORNeuralNetwork2()
{
    NeuralNetwork<float> network;
    std::vector<unsigned int> layerCounts;
    layerCounts.push_back(2);
    network.init(2,1,layerCounts, sigmoid<float>, sigmoid<float>, crossEntropy<float>, derivativeCrossEntropySigmoid<float>);

    network.randomWeights();

    srand(time(NULL));

    double rate = 0.02;

    for (int i = 0; i< 1000000; ++i)
    {
        int a = rand() % 2;
        int b = rand() % 2;
        int c = a ^ b;

        NeuralNetwork<float>::MiniBatch miniBatch;
        std::vector<float> labelVector;
        labelVector.push_back(c);


        std::vector<float> inputVector;
        inputVector.push_back(a);
        inputVector.push_back(b);

        NeuralNetwork<float>::TrainingData d(inputVector, labelVector);

        miniBatch.push_back(d);

        float cost;
        std::vector<NeuralNetworkLayer<float>> gradient;

        network.forwardPropagate(miniBatch, cost, gradient);
        qDebug() << "cost" << cost;

        if (i%500000 == 0)
        {
            rate*=0.5;
        }

        network.updateWeights(rate, gradient);
    }

    qDebug() << "Neural network for XOR has trained, now test:";

    int a[] = {0,0,1,1};
    int b[] = {0,1,0,1};
    for(int i = 0; i<4; ++i)
    {
        std::vector<float> inputs;
        inputs.push_back(a[i]);
        inputs.push_back(b[i]);
        std::vector<float> outputs;
        network.getResult(inputs, outputs);
        qDebug() << "a:" << a[i] << "b" << b[i] << "a XOR b" << (a[i]^b[i]) << "Neural Network computed:" << outputs[0];
    }

}

void testNeuralNetwork()
{
    testNeuralNetworkGradientCheck();
    testXORNeuralNetwork2();
}
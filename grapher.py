import matplotlib.pyplot as plt

def findAllFromTo(Text, Start, LenStart, End, LenEnd, Gap=0):
    lastIndex = 0
    __list = []
    iterations = Text.count(End)
    if Start == End:
        if Gap > 0 or iterations <= 2:
            iterations = int(iterations/2)
        elif iterations%2 == 1:
            iterations = int(iterations/2)*2
        else:
            iterations = iterations-1;
    for i in range(iterations):
        startIndex = Text.index(Start, lastIndex)+LenStart
        lastIndex = startIndex+1
        endIndex = Text.index(End, lastIndex)+LenEnd
        element = Text[startIndex:endIndex]
        __list.append(element)
        lastIndex = endIndex+Gap
    return __list

def str_to_list(String):
    return findAllFromTo(String, '\'', 1, '\'', 0, 1)

# def data_to_array(str d):
    
def time_gen(interval, amount):
    _list = []
    for i in range(amount):
        _list.append(i*interval)
    return _list

# d = 'b0eb0eb0.00444444eb0.00444444eb0.0311111eb0.0311111eb0.0694444eb0.0694444eb0.0861111eb0.0861111eb0.135556eb0.135556eb0.168889eb0.168889eb0.204444eb0.204444eb0.241111eb0.241111eb0.278889eb0.278889eb0.317778eb0.317778eb0.357778eb0.357778eb0.377778eb0.377778eb0.432222eb0.432222eb0.466667eb0.466667eb0.499444eb0.499444eb0.532222eb0.532222eb0.561111eb0.561111eb0.588333eb0.588333eb0.613333eb0.613333eb0.636667eb0.636667eb0.659444eb0.659444eb0.680556eb0.680556eb0.701111eb0.701111eb0.720556eb0.720556eb0.738889eb0.738889eb0.756111eb0.756111eb0.772222eb0.772222eb0.780556eb0.780556eb0.780556eb0.802778eb0.802778eb0.81eb0.81eb0.830556eb0.830556eb0.836667eb0.836667eb0.854444eb0.858889eb0.858889eb0.858889eb0.873889eb0.873889eb0.881667eb0.881667eb0.89eb0.896667eb0.896667eb0.902222eb0.902222eb0.908333eb0.908333eb0.910556eb0.910556eb0.917222eb0.917222eb0.922222eb0.922222eb0.924444eb0.924444eb0.924444eb0.931111eb0.933333eb0.933333eb0.933889eb0.933889eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.932778eb0.9'
# d= 'b0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.00277778eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0111111eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.0538889eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.122778eb0.122778eb0.122778eb0.12277778eb0.122778eb0.122778eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.161111eb0.360556eb0.360556eb0.360556eb0.360556eb0.360556eb0.360556eb0.360556eb0.360556eb0.360556eb0.360556eb0.360556eb0.360556eb0.360556eb0.399444eb0.399444eb0.399444eb0.399444eb0.399444eb0.399444eb0.399444eb0.399444eb0.399444eb0.320556eb0.520556eb0.520556eb0.520556eb0.520556eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567778eb0.567773eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.683333eb0.692222eb0.692222eb0.692222eb0.692222eb0.692222eb0.692222eb0.692222eb0.763889eb0.763889eb0.763889eb0.763889eb0.763889eb0.763889eb0.763889eb0.763889eb0.763889eb0.763889eb0.763889eb0.763889eb0.763889eb0.782778eb0.782778eb0.782778eb0.782778eb0.782778eb0.782778eb0.782778eb0.782778eb0.782778eb0.782222eb0.847222eb0.847222eb0.847222eb0.847222eb0.847222eb0.847222eb0.847222eb0.847222eb0.847222eb0.847222eb0.847222eb0.865eb0.865eb0.865eb0.865eb0.865eb0.865eb0.865eb0.865eb0.865eb0.865eb0.865eb0.865eb0.865eb0.865eb0.865eb0.8644eb0.889444eb0.889444eb0.889444eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.890.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.891667eb0.8916'
# d = 'b0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.07eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.105556eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.121667eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.155eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.207222eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.225556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.265556eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.323333eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667eb0.356667e'
# d = 'b0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.0488889eb0.0488889eb0.0488889eb0.0488889eb0.0488889eb0.0488889eb0.0488889eb0.0488889eb0.0488889eb0.0655556eb0.0655556eb0.0655556eb0.0655556eb0.0655556eb0.0655556eb0.0655556eb0.0655556eb0.0655556eb0.0655556eb0.0833333eb0.0833333eb0.0833333eb0.0833333eb0.0833333eb0.0833333eb0.0833333eb0.0833333eb0.0833333eb0.0833333eb0.0833333eb0.1eb0.1eb0.1eb0.1eb0.1eb0.1eb0.1eb0.1eb0.1eb0.115556eb0.115556eb0.115556eb0.115556eb0.115556eb0.115556eb0.115556eb0.115556eb0.115556eb0.115556eb0.133333eb0.133333eb0.133333eb0.133333eb0.133333eb0.133333eb0.133333eb0.133333eb0.133333eb0.133333eb0.152222eb0.152222eb0.152222eb0.152222eb0.152222eb0.152222eb0.152222eb0.152222eb0.152222eb0.152222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.195556eb0.195556eb0.195556eb0.195556eb0.195556eb0.195556eb0.195556eb0.195556eb0.195556eb0.195556eb0.216667eb0.216667eb0.216667eb0.216667eb0.216667eb0.216667eb0.216667eb0.216667eb0.216667eb0.216667eb0.216667eb0.236667eb0.236667eb0.236667eb0.236667eb0.236667eb0.236667eb0.236667eb0.236667eb0.236667eb0.254444eb0.254444eb0.254444eb0.254444eb0.254444eb0.254444eb0.254444eb0.254444eb0.254444eb0.254444eb0.274444eb0.274444eb0.274444eb0.274444eb0.274444eb0.274444eb0.274444eb0.274444eb0.274444eb0.274444eb0.292222eb0.292222eb0.292222eb0.292222eb0.292222eb0.292222eb0.292222eb0.292222eb0.292222eb0.292222eb0.311111eb0.311111eb0.311111eb0.311111eb0.311111eb0.311111eb0.311111eb0.311111eb0.311111eb0.311111eb0.33eb0.33eb0.33eb0.33eb0.33eb0.33eb0.33eb0.33eb0.33eb0.33eb0.35eb0.35eb0.35eb0.35eb0.35eb0.35eb0.35eb0.35eb0.35eb0.35eb0.35e'
# d = 'b0eb0eb0eb0eb0eb0eb0eb0eb0eb0eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00111111eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.00444444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.0144444eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.03eb0.0477778eb0.0477778eb0.0477778eb0.0477778eb0.0477778eb0.0477778eb0.0477778eb0.0477778eb0.0477778eb0.0477778eb0.0644444eb0.0644444eb0.0644444eb0.0644444eb0.0644444eb0.0644444eb0.0644444eb0.0644444eb0.0644444eb0.0644444eb0.0811111eb0.0811111eb0.0811111eb0.0811111eb0.0811111eb0.0811111eb0.0811111eb0.0811111eb0.0811111eb0.0811111eb0.0966667eb0.0966667eb0.0966667eb0.0966667eb0.0966667eb0.0966667eb0.0966667eb0.0966667eb0.0966667eb0.0966667eb0.0966667eb0.114444eb0.114444eb0.114444eb0.114444eb0.114444eb0.114444eb0.114444eb0.114444eb0.114444eb0.134444eb0.134444eb0.134444eb0.134444eb0.134444eb0.134444eb0.134444eb0.134444eb0.134444eb0.134444eb0.154444eb0.154444eb0.154444eb0.154444eb0.154444eb0.154444eb0.154444eb0.154444eb0.154444eb0.154444eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.172222eb0.19eb0.19eb0.19eb0.19eb0.19eb0.19eb0.19eb0.19eb0.19eb0.19eb0.19eb0.21eb0.21eb0.21eb0.21eb0.21eb0.21eb0.21eb0.21eb0.21eb0.23eb0.23eb0.23eb0.23eb0.23eb0.23eb0.23eb0.23eb0.23eb0.23eb0.248889eb0.248889eb0.248889eb0.248889eb0.248889eb0.248889eb0.248889eb0.248889eb0.248889eb0.248889eb0.27eb0.27eb0.27eb0.27eb0.27eb0.27eb0.27eb0.27eb0.27eb0.27eb0.288889eb0.288889eb0.288889eb0.288889eb0.288889eb0.288889eb0.288889eb0.288889eb0.288889eb0.288889eb0.288889eb0.31eb0.31eb0.31eb0.31eb0.31eb0.31eb0.31eb0.31eb0.31eb0.328889eb0.328889eb0.328889eb0.328889eb0.328889eb0.328889eb0.328889eb0.328889eb0.328889eb0.328889eb0.347778eb0.347778eb0.347778eb0.347778eb0.347778eb0.347778eb0.347778eb0.347778eb0.347778eb0.347778eb0.367778eb0.367778eb0.367778eb0.367778eb0.367778eb0.36777'
# d = 'b0eb0eb0.00333333eb0.0122222eb0.0266667eb0.0266667eb0.0577778eb0.0577778eb0.0955556eb0.0955556eb0.136667eb0.158889eb0.178889eb0.2eb0.21eb0.236667eb0.236667eb0.28eb0.301111eb0.323333eb0.343333eb0.363333eb0.383333eb0.403333eb0.422222eb0.422222eb0.46eb0.46eb0.496667eb0.514444eb0.531111eb0.547778eb0.563333eb0.578889eb0.593333eb0.607778eb0.615556eb0.615556eb0.65eb0.663333eb0.676667eb0.69eb0.702222eb0.714444eb0.714444eb0.725556eb0.747778eb0.758889eb0.771111eb0.771111eb0.794444eb0.805556eb0.818889eb0.83eb0.841111eb0.852222eb0.863333eb0.873333eb0.878889eb0.892222eb0.901111eb0.91eb0.91eb0.925556eb0.925556eb0.933333eb0.945556eb0.952222eb0.956667eb0.961111eb0.965556eb0.965556eb0.972222eb0.972222eb0.975556eb0.975556eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.976667eb0.9'
# d = 'b0eb0eb-0.0144444eb-0.03eb-0.0666667eb-0.08eb-0.1eb-0.108889eb-0.118889eb-0.147778eb-0.178889eb-0.196667eb-0.235556eb-0.255556eb-0.29eb-0.306667eb-0.335556eb-0.35eb-0.374444eb-0.385556eb-0.405556eb-0.416667eb-0.425556eb-0.444444eb-0.452222eb-0.472222eb-0.494444eb-0.505556eb-0.515556eb-0.535556eb-0.554444eb-0.563333eb-0.571111eb-0.586667eb-0.598889eb-0.605556eb-0.614444eb-0.618889eb-0.621111eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556eb-0.625556e'
# d = 'b0eb0eb0.00444444eb0.0133333eb0.0255556eb0.04eb0.04eb0.0755556eb0.0933333eb0.111111eb0.128889eb0.128889eb0.166667eb0.184444eb0.202222eb0.202222eb0.24eb0.261111eb0.282222eb0.302222eb0.324444eb0.345556eb0.366667eb0.376667eb0.376667eb0.417778eb0.417778eb0.455556eb0.471111eb0.487778eb0.502222eb0.517778eb0.517778eb0.531111eb0.556667eb0.556667eb0.58eb0.58eb0.602222eb0.612222eb0.622222eb0.622222eb0.636667eb0.656667eb0.656667eb0.68eb0.693333eb0.705556eb0.717778eb0.717778eb0.742222eb0.742222eb0.754444eb0.776667eb0.786667eb0.796667eb0.796667eb0.806667eb0.823333eb0.831111eb0.837778eb0.844444eb0.848889eb0.854444eb0.857778eb0.862222eb0.864444eb0.866667eb0.867778eb0.867778eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868889eb0.868'
print('Enter data: ')
d = input()
# t = 'b0eb10eb20eb30eb40eb50eb60eb70eb80eb90eb100eb110eb120eb130eb140eb150eb160eb170eb180eb190eb200eb210eb220eb230eb240eb250eb260eb270eb280eb290eb300eb310eb320eb330eb340eb350eb360eb370eb380eb390eb400eb410eb420eb430eb440eb450eb460eb470eb480eb490eb500eb510eb520eb530eb540eb550eb560eb570eb580eb590eb600eb610eb620eb630eb640eb650eb660eb670eb680eb690eb700eb710eb720eb730eb740eb750eb760eb770eb780eb790eb800eb810eb820eb830eb840eb850eb860eb870eb880eb890eb900e'
data = findAllFromTo(d, 'b', 1, 'e', 0)
# time = findAllFromTo(t, 'b', 1, 'e', 0)
gen = time_gen(10, len(data))
print(len(data))
# print(len(time))
print(len(gen))

plt.plot(gen, data)

plt.show()
\* pork.lp *\
Maximize
value: 8 Nhf + 14 Nhs + 11 Nho + 4 Nbf + 12 Nbs + 7 Nbo + 4 Npf + 13 Nps + 9 Npo

Subject To
fresh: Nhf + Nhs + Nho = 480
belly: Nbf + Nbs + Nbo = 400
picnc: Npf + Nps + Npo = 230
smoke: Nhs + Nbs + Nps <= 420
otsmk: Nho + Nbo + Npo <= 250

Bounds
Nhf >= 0 \number of hams, fresh
Nhs >= 0 \number of hams, smoked
Nho >= 0 \number of hams, smoked on overtime
Nbf >= 0 \number of pork bellies, fresh
Nbs >= 0 \number of pork bellies, smoked
Nbo >= 0 \number of pork bellies, smoked on overtime
Npf >= 0 \number of picnic hams, fresh
Nps >= 0 \number of picnic hams, smoked
Npo >= 0 \number of picnic hams, smoked on overtime

End

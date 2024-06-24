%% Acid Base Disorder Diagnosis
% by Tiffany Nguyen

%% Test Diagonsis Function
fprintf("Sample 1: pH = 5, bicarbonate = 20 mEq/L, PCO2 = 30 mmHg\n")
acidBaseDiagnosis(5, 20, 30)
fprintf("\nSample 2: pH = 5, bicarbonate = 20 mEq/L, PCO2 = 45 mmHg\n")
acidBaseDiagnosis(5, 20, 45)
fprintf("\nSample 3: pH = 7.5, bicarbonate = 25 mEq/L, PCO2 = 40 mmHg\n")
acidBaseDiagnosis(7.5, 25, 40)
fprintf("\nSample 4: pH = 9, bicarbonate = 26 mEq/L, PCO2 = 41 mmHg\n")
acidBaseDiagnosis(9, 26, 41)

%% Diagnosis Function
function acidBaseDiagnosis(pH, bicarbonate, PCO2)
    % acidBaseDiagnosis - provides information about acid base diagnosis
    % 
    % Parameters:
    %   pH (float): pH value
    %   bicarbonate (float): bicarbonate concentration (in units of mEq/L)
    %   PCO2 (float): PCO2 pressure (in units of mmHg)
    % 
    % Output:
    %   nothing
    % 
    % Print: 
    %   prints out acid-base diagonosis and compensation if present
    if pH < 7.4
        if bicarbonate < 24
            disp("Diagnosis: Metabolic Acidiosis")
            if PCO2 < 40 %check compensation if have Metabolic Acidiosis
                disp("Respiratory compensation present")
            end
        end
        if PCO2 > 40 %respiratory acidosis is 2nd possible diagnosis when pH is <7.4
            disp("Diagnosis: Respiratory acidosis")
            if bicarbonate > 24 %check compensation if have respiratory acidosis
               disp("Renal compensation present")
            end
        end
    elseif pH > 7.4 %when pH > 7.4, use elseif not else so doesn't get displayed when pH = 7.4
        if bicarbonate > 24
            disp("Diagnosis: Metabolic alkalosis")
            if PCO2 > 40 %check compensation if have metabolic alkalosis
                disp("Respiratory compensation present")
            end
        end
        if PCO2 < 40 %Respiratory alkalosis is 2nd possible diagnosis when pH is >7.4
            disp("Diagnosis: Respiratory alkalosis")
            if bicarbonate < 24 %check compensation if have respiratory alkalosis
                disp("Renal compensation present")
            end
        end
    end
end
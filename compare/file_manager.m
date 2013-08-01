%% This program copy the files generated after the tests into some directories where it's more convenient to work


flauta_dir = '/home/paul/flauta/';     %% sources files directory
output_dir = '/home/paul/compare/';    %% destination directory (here)

endpoints = {...
    'bernoulli',...
    'blow',...
    'excitation',...
    'jet',...
    'jetdrive',...
    'receptivity',...
    'sources',...
    'turbulence',...
    'vortex',...
    'resonator'};

noutputs = {...
    2,...
    1,...
    2,...
    3,...
    2,...
    2,...
    3,...
    1,...
    1,...
    2};

% exclue the modules that you don't want to analyze

exclude = [1 2 3 4 5 6 7 8 9];

for i = 1:length(exclude)
    endpoints{exclude(i)} = [];
    noutputs{exclude(i)} = [];
end
endpoints = endpoints(~cellfun('isempty',endpoints));
noutputs = noutputs(~cellfun('isempty',noutputs));

ntests = 6;

for i=1:length(endpoints)
    
    
    source = [flauta_dir 'gen/' endpoints{i} '_out_'];
    
    dest_orig = [output_dir 'cpp/' endpoints{i} '/' endpoints{i} '_out_'];
    dest_faust = [output_dir 'faust/' endpoints{i} '/' endpoints{i} '_out_'];
    
    switch noutputs{i}
        case 1
            tests = allcomb(1:ntests);
        case 2
            tests = allcomb(1:ntests,1:ntests);
        case 3
            tests = allcomb(1:ntests,1:ntests,1:ntests);
        case 4
            tests = allcomb(1:ntests,1:ntests,1:ntests,1:ntests);
    end
    
    for j = 1:size(tests,1)
        source_orig = source;
        source_faust = source;
        dest_orig_final = dest_orig;
        dest_faust_final = dest_faust;
        
        for k = 1:size(tests,2)
            source_orig = [source_orig num2str(tests(j,k))];
            source_faust = [source_faust num2str(tests(j,k))];
            dest_orig_final = [dest_orig_final num2str(tests(j,k))];
            dest_faust_final = [dest_faust_final num2str(tests(j,k))];
        end
        
        source_orig = [source_orig '_orig.txt']
        source_faust = [source_faust '_faust.txt'];
        dest_orig_final = [dest_orig_final '_orig.txt']
        dest_faust_final = [dest_faust_final '_faust.txt'];
        copyfile(source_orig,dest_orig_final);
        copyfile(source_faust,dest_faust_final);
    end    
end
